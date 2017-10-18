#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
int xlab, ylab;
char **lab;

void Lucas(int xlab, int ylab);


int main()
{
	fstream plik;
	plik.open("labirynt.txt", ios::in | ios::out);
	if (plik.good() == true)
	{
		{
			plik >> xlab;
			plik >> ylab;

			int litera = 33;

			lab = (char**)malloc(xlab * sizeof(char *)); //alokacja pamieci
			for (int i = 0; i < xlab; i++)
			{
				lab[i] = (char*)malloc(ylab * sizeof(char));

				for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
				{
					lab[i][j] = (litera);
					litera++;
				}

			}
			cout << "xlab== " << xlab << endl;
			cout << "ylab== " << ylab << endl;

			for (int i = 0; i < xlab; ++i, printf("\n"))
				for (int j = 0; j < ylab; ++j)
					printf("%.1c\t", lab[i][j]);
		}




		plik.close();
	}

	system("Pause");

	return 0;
}

/*
void Lucas(int xlab, int ylab)
{
	int l=0,n=0;

	if (n == 0)
	{
		l = 2;
	}else
	{if(n==1) }

	for (;n > 1;)
	{

	}
}
*/

//char lab[xlab][ylab] = {};
