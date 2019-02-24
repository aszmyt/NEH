#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <ctime>
#define MAX_MASZYN 22
#define MAX_ZADAN 503

using namespace std;

class Zadania
{
    public:
	int czas;
	int suma;
	int zadanie;
	bool operator < (const Zadania &a)const {return suma>a.suma;}
};


Zadania R[MAX_ZADAN][MAX_MASZYN];
Zadania Q[MAX_ZADAN][MAX_MASZYN];
Zadania ZAD[MAX_MASZYN];
Zadania* pomoc;
int Liczcmax(int zadanie,int masz)
{
	int cmax = 0;

    Zadania Rzad[MAX_MASZYN+1];
	Zadania Qzad[MAX_MASZYN+1];

    for (int i = 0; i <= masz + 1; i++){Rzad[i].czas = 0; Qzad[i].czas = 0;}
    for (int i = masz; i >= 1; i--)Qzad[i].czas = max(Q[zadanie+1][i].czas, Qzad[i+1].czas) + ZAD[i-1].czas;
    for (int i = 1; i <= masz; i++)Rzad[i].czas = max(R[zadanie][i].czas, Rzad[i-1].czas) + ZAD[i-1].czas;
    for (int i = 1; i <= masz; i++)if((Rzad[i].czas + Qzad[i].czas - ZAD[i-1].czas) > cmax) cmax = Rzad[i].czas + Qzad[i].czas - ZAD[i-1].czas;
     return cmax;
}

void neh(Zadania tmp[MAX_ZADAN][MAX_MASZYN], Zadania dane[MAX_ZADAN][MAX_MASZYN],int masz, int zadan)
{
	int CMAX = 0;
	int maxi = 0;
	int najlepszy = 0;
	for (int y = 1; y < zadan; y++)
	{
		for (int j = 0; j < masz; j++){
            ZAD[j] = dane[pomoc[y].zadanie-1][j];
            }

        for (int i = 0; i <= zadan + 1; ++i){
            for (int j = 0; j <= masz + 1; ++j){
                R[i][j].czas=0;
                }
            }

        for (int i = 1; i <= zadan; ++i){
            for (int j = 1; j <= masz; ++j){
                R[i][j].czas = max(R[i-1][j].czas, R[i][j-1].czas) + tmp[i-1][j-1].czas;
                }
            }

        for (int i = y + 2; i > 0; i--){
            for (int j = masz + 2; j > 0; j--){
                Q[i][j].czas = 0;
                }
            }

        for (int i = y; i >= 0; --i){
            for (int j = masz; j >= 0 ; --j){
                Q[i][j].czas = max(Q[i+1][j].czas, Q[i][j+1].czas) + tmp[i-1][j-1].czas;
                }
            }

        for (int i = zadan; i > y; --i){
            for (int j = 0; j < masz; j++){
                tmp[i][j] = tmp[i-1][j];
                }
            }

		for (int i = 0; i < masz; i++) {tmp[y][i]= ZAD[i];}

		CMAX = Liczcmax(y,masz);
		najlepszy = y;

		for (int k = y; k > 0; k--){
			for(int j = 0; j < masz; j++){
                swap(tmp[k][j],tmp[k-1][j]);
                }
			maxi = Liczcmax(k-1,masz);
			if (maxi <= CMAX){
                CMAX = maxi; najlepszy = k-1;
            }
		}

		for (int i = 0; i < najlepszy; i++)
			for (int j = 0; j < masz; j++){
                tmp[i][j] = tmp[i+1][j];
            }
		// Wstawienie Zadania
		for (int j = 0; j<masz; j++){
            tmp[najlepszy][j]= ZAD[j];
        }
	}
	cout<<CMAX<<"\t";
}

int main()
{
ifstream plik;
int m,n,ww,k;
plik.open( "data000.txt" );
Zadania tablica[MAX_ZADAN][MAX_MASZYN];
Zadania tab_wyn[MAX_ZADAN][MAX_MASZYN];
clock_t start = clock();
for (k = 0; k < 121; k++) // 120 = ilosc zadan
{
    clock_t start2 = clock();
	int wynik = 0;
	plik >> n >> m;
	pomoc = new Zadania[n];
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			tablica[i][j].zadanie = i+1;
			plik >> tablica[i][j].czas;
		}
	}
	for (int i = 0; i < n; i++){
		tablica[i][0].suma = 0;
		for (int j = 0; j < m; j++){
			tablica[i][0].suma = tablica[i][0].suma + tablica[i][j].czas;
		}
	}

	for (int j = 0; j < n; j++){
		pomoc[j] = tablica[j][0];
	}

	stable_sort(pomoc,pomoc+n);

	for(ww = 0; ww < m; ww++){
		tab_wyn[0][ww] = tablica[pomoc[0].zadanie-1][ww];
	}

    cout<<"data."<<k<<"  \t";
    neh(tab_wyn, tablica,m,n);
    printf( ": %lu ms\n", clock() - start2 );
}
printf( "\nCzas wykonywania ogolem: %lu ms\n", clock() - start );
system("pause");
plik.close();
return 0;
}
