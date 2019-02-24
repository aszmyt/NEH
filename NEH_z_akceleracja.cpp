#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#define MAX_M 22
#define MAX_N 502
#include <sstream>
#include <windows.h>

using namespace std;


struct neh_a
{
	int czas_trwania;
	int w;//suma czasow wykonywania zadania na wszystkich maszynach
	int numer_zadania;
	bool operator < (const neh_a &x)const //zdefiniowanie zachowania siê operatora < potrzebnego przy sortowaniu
	  {
	    return w>x.w;
	  }
};


neh_a ZAD[MAX_M];
neh_a R[MAX_N][MAX_M];
neh_a Q[MAX_N][MAX_M];
neh_a* proces;

int n;	// liczba zadan
int m;	// liczba maszyn

/*Algorytm licznia NEH z akceleracja zastal napisany na podstawie*/
/*http://www.kierunkizamawiane.pwr.wroc.pl/materialy/smut.pdf    */
/*strony 237-238												 */

// Liczenie macierzy R (od poczatku grafu)
void macierz_R(neh_a tab[MAX_N][MAX_M], int _n, int _m)
{
	for (int i = 0; i <= _n + 1; ++i)
		for (int j = 0; j <= _m + 1; ++j)
			R[i][j].czas_trwania=0;

	for (int i = 1; i <= _n; ++i)
		for (int j = 1; j <= _m; ++j)
			R[i][j].czas_trwania = max(R[i-1][j].czas_trwania, R[i][j-1].czas_trwania) + tab[i-1][j-1].czas_trwania;
}

// Liczenie macierzy Q (od konca grafu)
void macierz_Q(neh_a tab[MAX_N][MAX_M], int _n, int _m)
{
	for (int i = _n + 2; i > 0; i--)
		for (int j = _m + 2; j > 0; j--)
			Q[i][j].czas_trwania = 0;


	for (int i = _n; i >= 0; --i)
		for (int j = _m; j >= 0 ; --j)
			Q[i][j].czas_trwania = max(Q[i+1][j].czas_trwania, Q[i][j+1].czas_trwania) + tab[i-1][j-1].czas_trwania;
}


int _Cmax(int numer_zadania)
{
	int Cmax = 0;

    neh_a zad_R[MAX_M+1];
	neh_a zad_Q[MAX_M+1];

    for (int i = 0; i <= m + 1; i++){
		zad_R[i].czas_trwania = 0;
		zad_Q[i].czas_trwania = 0;
	}

    for (int i = m; i >= 1; i--)
		zad_Q[i].czas_trwania = max(Q[numer_zadania+1][i].czas_trwania, zad_Q[i+1].czas_trwania) + ZAD[i-1].czas_trwania;

    for (int i = 1; i <= m; i++)
		zad_R[i].czas_trwania = max(R[numer_zadania][i].czas_trwania, zad_R[i-1].czas_trwania) + ZAD[i-1].czas_trwania;

    for (int i = 1; i <= m; i++)
		if((zad_R[i].czas_trwania + zad_Q[i].czas_trwania - ZAD[i-1].czas_trwania) > Cmax)
			Cmax = zad_R[i].czas_trwania + zad_Q[i].czas_trwania - ZAD[i-1].czas_trwania;

     return Cmax;
}

//Wstawianie zadania na miejsce index
void insertAt(neh_a ZAD[MAX_M], neh_a tab[MAX_N][MAX_M], int n, int m, int index) {

    for (int i = n; i > index; --i)
    	for (int j = 0; j < m; j++)
        tab[i][j] = tab[i-1][j];

		for (int i = 0; i < m; i++)
		tab[index][i]= ZAD[i];

}


int NEH_akceleracja(neh_a tmp[MAX_N][MAX_M], neh_a dane[MAX_N][MAX_M])
{
	int minimum = 0;
	int best = 0;
	for (int y = 1; y < n; y++)
	{
		for (int j = 0; j < m; j++)
		ZAD[j] = dane[proces[y].numer_zadania-1][j];

		macierz_R(tmp,y,m);
		macierz_Q(tmp,y,m);

		insertAt(ZAD,tmp,y,m,y);
		int Cmax = _Cmax(y);
		minimum = Cmax;			// Minimalny Cmax
		best = y;

		// Przesuwanie zadania
		for (int k = y; k > 0; k--){
			for(int j = 0; j < m; j++)
				swap(tmp[k][j],tmp[k-1][j]);
			// Liczenie Cmax
			Cmax = _Cmax(k-1);
			// Sprawdzenie Cmaxa
			if (Cmax <= minimum){
				minimum = Cmax;
				best = k-1;
			}
		}

		for (int i = 0; i < best; i++)
			for (int j = 0; j < m; j++)
				tmp[i][j] = tmp[i+1][j];
		// Wstawienie zadania
		for (int j = 0; j<m; j++)
			tmp[best][j]= ZAD[j];

	}
	return minimum;
}



void wstaw_dane(string name,neh_a tmp[MAX_N][MAX_M]){

	ifstream plik;
	plik.open( name.c_str() );
	plik >> n >> m;

	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			tmp[i][j].numer_zadania = i+1;
			plik >> tmp[i][j].czas_trwania;
		}
	}
	plik.close();
}

int main()
{

neh_a dane[MAX_N][MAX_M];
neh_a tmp[MAX_N][MAX_M];
LARGE_INTEGER frequency;        // ticks per second
LARGE_INTEGER t1, t2;           // ticks
double elapsedTime;
QueryPerformanceFrequency(&frequency);


fstream plik_perm,plik_cmax;
plik_perm.open("permutacje_a.txt", fstream::out);
plik_cmax.open("cmax_a.txt", fstream::out);

for (int z = 0; z < 121; z++) // 120 = ilosc zadan
{
	string nazwa_instancji;
	int wynik = 0;
	int minimum = 0;
	int best = 0;

	string name;
	string str;
	ostringstream numer;


	numer << z;
	if(z<10)
	str = "00"+numer.str();
	else if(z >= 10 && z <100)
	str = "0"+numer.str();
	else if(z >=100)
	str = numer.str();
	wstaw_dane("data."+str+".txt",dane);


	proces = new neh_a[n];
	for (int i = 0; i < n; i++)
	{
		dane[i][0].w = 0;

		for (int j = 0; j < m; j++)
			dane[i][0].w = dane[i][0].w + dane[i][j].czas_trwania;
	}

	for (int j = 0; j < n; j++)
		proces[j] = dane[j][0];


	stable_sort(proces,proces+n);

	for(int k = 0; k < m; k++)
		tmp[0][k] = dane[proces[0].numer_zadania-1][k];

	QueryPerformanceCounter(&t1);
	wynik = NEH_akceleracja(tmp, dane);
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

	cout << z << ": Cmax: " << wynik << endl;
	plik_cmax << "data."+str+".txt :" << wynik << " Czas wykonania: "<< elapsedTime << " ms.\n" << endl;
	// Wypisanie permutacji
	plik_perm << "Permutacja " << z << ": ";
	for (int i=0; i<n; i++)
		plik_perm << tmp[i][0].numer_zadania << " ";
	plik_perm << endl << endl;
}

plik_perm.close();
plik_cmax.close();
system("pause");
return 0;
}
