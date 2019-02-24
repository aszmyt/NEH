#include <iostream>
#include <cmath>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

void neh(int tab_cmax[],int tab_wyn[][2],int tablica[],int n,int m)
{
    int r[n][m];
    int cmax=0;
    int q[n][m];
    int pom[n][m];
    int pom1[n][m];
    int pom2[n][m];
    int kolejnosc[n];
    int tmp[n];
    int tmp1[n];
    int tmp2[n];
    int wartosc=0;
        for(int k=0;k<n;k++)
    {
        for(int w=0;w<m;w++)
        {
            pom[k][w]=0;
            pom1[k][w]=0;
            pom2[k][w]=0;
            r[k][w]=0;
            q[k][w]=0;
        }
    }
    int zmienna=0;
    for(int i=0;i<n;i++)
    {
        zmienna=0;
        cmax=9999999999;
            for(int l=0;l<i+1;l++)
            {
                    zmienna=tab_wyn[i][0]*m-m;
                for(int j=0;j<i+1;j++)
                {
                    if(j<l)
                    {
                        for(int k=0;k<m;k++)
                        {
                            pom1[j][k]=pom[j][k];
                            tmp1[j]=tmp[j];
                        }
                    }
                    else if(j==l)
                    {
                        for(int k=0;k<m;k++)

                        {
                            pom1[j][k]=tablica[zmienna+k];
                          tmp1[j]=tab_wyn[i][0];

                        }

                    }
                    else if(j>l)
                    {
                        for(int k=0;k<m;k++)
                        {
                            pom1[j][k]=pom[j-1][k];
                            tmp1[j]=tmp[j-1];
                        }
                    }
                    }
//---------------------------------------------------------------------------------//
//------------------------------------liczenie cmax--------------------------------//
                  for(int k=l-1;k<i+1;k++)
                  {
                      for(int w=0;w<m;w++)
                      {
                        if(k==0)
                        {
                            if(w==0)
                            {
                                r[0][0]=pom1[0][0];
                               // q[k][w]=pom1[i][m-1];
                            }
                            else if(w>0)
                            {
                                r[k][w]=r[k][w-1]+pom1[k][w];
                               // q[k][w]=q[k][w-1]+pom1[i][m-w-1];
                            }
                        }
                        else if(k>0)
                        {
                            if(w==0)
                            {
                                r[k][w]=r[k-1][w]+pom1[k][0];
                               // q[k][w]=q[k-1][w]+pom1[i-k+1][m-1];
                            }
                            else if(w>0)
                            {
                                r[k][w]=max(r[k-1][w],r[k][w-1])+pom1[k][w];
                               // q[k][w]=0;
                            }
                        }
                      }
                  }
//---------------------------------KONIEC LICZENIA-----------------------------------//
//-----------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------//
//------------------------------------WYBIERANIE NAJLEPSZEGO CMAX--------------------//
                    if(cmax>r[i][m-1])
                    {
                    for(int x=0;x<i+1;x++)
                {



                    for(int k=0;k<m;k++)
                    {
                        pom2[x][k]=pom1[x][k];
                        tmp2[x]=tmp1[x];

                       //cout<<" "<<pom1[x][k];
                    }
                }


                cmax=r[i][m-1];
        }
//----------------------------------------------------------------------------------------//
//----------------------KONIEC WYBIERANIA CMAX--------------------------------------------//


            }
                    for(int x=0;x<i+1;x++)
                {
                    for(int k=0;k<m;k++)
                    {
                        pom[x][k]=pom2[x][k];
                    }
                    tmp[x]=tmp2[x];
                }

}	int ww;
for(int ww=0;ww<n;ww++)
{
 //   cout<<tmp[ww]<<" ";
}
cout<<"cmax= "<<cmax<<endl;
}



void Sortowanie( int tab[][2], int left, int right )
{
    int i = left;
    int j = right;
    int x = tab[( left + right-1 ) / 2 +1][1];
    do
    {
        while( tab[ i ][1] > x )
             i++;
        while( tab[ j ][1] < x )
             j--;
        if( i <= j )
        {
            for(int p=0;p<2;p++)
            {
            swap( tab[ i ][p], tab[ j ][p] );
            }
            i++;
            j--;
        }
    } while( i <= j );
    if( left < j ) Sortowanie( tab, left, j );
    if( right > i ) Sortowanie( tab, i, right );
}
void wyswietl(int n, int m,int *tablica)
{
        for(int i=0;i<n*m;i++)
    {

        cout<<tablica[i]<<" ";
            if(i%m==2)
    {
        cout<<endl;
    }}
}

int main()
{
    ifstream plik;
	plik.open("data000.txt");
	for(int k=0;k<120;k++){
    int n,m;
    int pom=1;
	plik>>n;
	plik>>m;
	int tablica[n*m];
	int tab[n];
	int tab_wyn[n][2];
	for(int i=0;i<n*m;i++)
    {
        plik>>tablica[i];
    }
    cout<<"data."<<k+1<<"  \t";
    for(int i=0;i<n;i++)
    {
        tab[i]=0;
        for(int j=0;j<m;j++){
        tab[i]=tab[i]+tablica[i*m+j];
        }
    }
 for(int j=0;j<n;j++)
    {
        for(int i=0;i<2;i++)
        {
            if(i==0)
            {
                tab_wyn[j][i]=pom;
                pom++;
            }
            else{
            tab_wyn[j][i]=tab[j];
            }
        }
    }

    Sortowanie(tab_wyn,0,n-1);

   int tmp=tab_wyn[0][0];
   int tab_cmax[n*m];
     neh(tab_cmax,tab_wyn,tablica,n,m);
	}
    plik.close();
    return 0;
}
