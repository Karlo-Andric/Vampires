#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <assert.h>
using namespace std;
class KoordinateMatrice
{
public:
    int row;
    int col;
};
void unos(int **niz, int redova, int kolona)
{
    for (int i = 0; i < redova; i++)
    {
        for (int j = 0; j < kolona; j++)
        {
            niz[i][j] = 0;
        }
    }
    niz[0][0] = 1;
}
void alokacija(int **&niz, int &redova, int &kolona)
{
    cout << "Unesite dimenzije matrice: ";
    cin >> redova >> kolona;
    niz = new int *[redova];
    assert(niz != nullptr);
    for (int i = 0; i < redova; i++)
        niz[i] = new int[kolona];
}
void ispis(int **niz, int redova, int kolona)
{
    for (int i = 0; i < redova; i++)
    {
        for (int j = 0; j < kolona; j++)
            cout << "+----";
        cout << "+" << endl;
        for (int j = 0; j < kolona; j++)
            cout << "|" << setw(4) << niz[i][j];
        cout << "|" << endl;
    }
    for (int j = 0; j < kolona; j++)
        cout << "+----";
    cout << "+" << endl;
}
void dealokacija(int **&niz, int redova)
{
    for (int i = 0; i < redova; i++)
        delete[] niz[i];
    delete[] niz;
    niz = nullptr;
}
bool ima_li_Zivih(int **niz, int redova, int kolona)
{
    for (int i = 0; i < redova; i++)
    {
        for (int j = 0; j < kolona; j++)
        {
            if (niz[i][j] != 1)
                return true;
        }
    }
    return false;
}
void trenutniVampiri(int **niz, int redova, int kolona, vector<KoordinateMatrice> &x)
{
    for (int i = 0; i < redova; i++)
    {
        for (int j = 0; j < kolona; j++)
        {
            if (niz[i][j] == 1)
            {
                KoordinateMatrice koordinate;
                koordinate.row = i;
                koordinate.col = j;
                x.push_back(koordinate);
            }
        }
    }
};
void trazenjeINapadanjeZrtava(int **niz, int redova, int kolona, int maxRowSize, int maxColSize)
{
    vector<KoordinateMatrice> moguceZrtve;
    KoordinateMatrice temp;
    random_device rd;
    mt19937 generator(rd());
    if (niz[redova][kolona] == 1)
    {
        if (redova > 0)
        {
            int ix = redova - 1; // gornji komsija
            //  KoordinateMatrice temp;
            temp.row = ix;
            temp.col = kolona;
            moguceZrtve.push_back(temp);
        }
        if (kolona > 0)
        {
            int jx = kolona - 1; // lijevi komsija
            //  KoordinateMatrice temp;
            temp.row = redova;
            temp.col = jx;
            moguceZrtve.push_back(temp);
        }
        if (redova < maxRowSize - 1)
        {
            int xi = redova + 1; // donji komsija
            //  KoordinateMatrice temp;
            temp.row = xi;
            temp.col = kolona;
            moguceZrtve.push_back(temp);
        }
        if (kolona < maxColSize - 1) // desni komsija
        {
            int xj = kolona + 1;

            //  KoordinateMatrice temp;
            temp.row = redova;
            temp.col = xj;
            moguceZrtve.push_back(temp);
        }
        uniform_int_distribution<int> distribution(0, moguceZrtve.size() - 1);
        int randomNumber = distribution(generator);
        if (!moguceZrtve.empty())
        {
            KoordinateMatrice randomZrtva = moguceZrtve[randomNumber];
            int rNum = randomNumber;
            int x = randomZrtva.row;
            int y = randomZrtva.col;
            niz[x][y] = 1;
            moguceZrtve.clear();
        }
    }
}
int main()
{
    vector<KoordinateMatrice> sviVampiri;
    int kraj = 1;
    int **niz = nullptr;
    int redova = 0, kolona = 0;
    int count = 0;
    alokacija(niz, redova, kolona);
    unos(niz, redova, kolona);
    int x = redova;
    int y = kolona;
    do
    {
        trenutniVampiri(niz, redova, kolona, sviVampiri);
        for (int i = 0; i < sviVampiri.size(); i++)
        {
            trazenjeINapadanjeZrtava(niz, sviVampiri[i].row, sviVampiri[i].col, x, y);
        }
        ispis(niz, redova, kolona);
        ++count;
        cout << " Broj sati: " << count;
        cout << endl
             << "Za nastavak <1>, za kraj <0>: ";
        cin >> kraj;
    } while (ima_li_Zivih(niz, redova, kolona) == true);
    dealokacija(niz, redova);
}