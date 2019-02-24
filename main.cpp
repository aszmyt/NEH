#include <iostream>
#include <cmath>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

void neh(int tab_wyn[][1],int tablica[][20],int n,int m)
{
    int r[n][m];
    int cmax=0;
    int q[n][m];
    int pom[n][m];
    int pom1[n][m];
    int pom2[n][m];
    int kolejnosc[n];
    int tmp[n];
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

             //  cout<<pom[0][0]<< "   "<<pom[0][1]<< "   "<<pom[0][2]<< "   ";

cout<<endl<<endl;
    for(int i=0;i<n;i++)
    {
        zmienna=0;
        cmax=9999999999;
            for(int l=0;l<i+1;l++)
            {
                    zmienna=tab_wyn[i][0]*m-m;

                    //cout<<zmienna<< "<--- zmienna"<<endl;
                for(int j=0;j<i+1;j++)
                {
                    if(j<l)
                    {
                        for(int k=0;k<m;k++)
                        {
                            pom1[j][k]=pom[j][k];
                        }
                    }
                    else if(j==l)
                    {
                        for(int k=0;k<m;k++)
                        {
                            pom1[j][k]=tablica[zmienna][k];
                          tmp[i]=tab_wyn[i][0];

                        }

                    }
                    else if(j>l)
                    {
                        for(int k=0;k<m;k++)
                        {
                            pom1[j][k]=pom[j-1][k];
                        }
                    }
                    }
//---------------------------------------------------------------------------------//
//------------------------------------liczenie cmax--------------------------------//
                  for(int k=0;k<i+1;k++)
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

                       // cout<<" "<<pom1[x][k];
                    }
                  //  tmp2[x]=tmp[x];
                }


                cmax=r[i][m-1];
        }
//----------------------------------------------------------------------------------------//
//----------------------KONIEC WYBIERANIA CMAX--------------------------------------------//


                  for(int k=0;k<i+1;k++)
                  {
                     // cout<<endl;
                      for(int w=0;w<m;w++)
                      {
                        //  cout<<"  r= "<<r[k][w];//<<"   q= "<<q[k][w];
                      }
                     // cout<<endl;
                  }
            }
                    for(int x=0;x<i+1;x++)
                {
                    for(int k=0;k<m;k++)
                    {
                        pom[x][k]=pom2[x][k];
                    }
                    kolejnosc[x]=tmp2[x];
                }

}
cout<<"cmax= "<<cmax<<endl;
                for(int k=0;k<n;k++)
                  {
                      cout<<endl;
                      for(int w=0;w<m;w++)
                      {
                          cout<<"  r= "<<r[k][w];//<<"   q= "<<q[k][w];
                      }
                      cout<<endl;
                  }
}


void Sortowanie( int tab[][1], int left, int right )
{
    int i = left;
    int j = right;
    int x = tab[( left + right ) / 2 ][1];
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

int main()
{
    ifstream plik;
	plik.open("data000.txt");
	for(int k=0;k<1;k++)
        {
            int n,m;
            plik>>n;
            plik>>m;
            int tab[n][m+1];
            int tab1[n][1];
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<m+1;j++)
                {
                    if(j==0){tab[i][j]=i;}
                    else{plik>>tab[i][j];}
                }
            }
                for(int i=0;i<n;i++)
            {
                tab1[i][1]=0;
                for(int j=1;j<m+1;j++){ tab1[i][1]=tab1[i][1]+tab[i][j]; tab1[i][0]=tab[i][0]; }
            }
            Sortowanie(tab1,0,n-1);
            neh(tab1,tab,n,m);
        }
return 0;
}
