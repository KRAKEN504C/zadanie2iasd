#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;
int xlab, ylab;

void Lucas();

void Printing(int xlab,int ylab,char** lab);

void botStart(int xlab, int ylab, char** lab, int *startPointx, int *startPointy);
void botMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy);

int main()
{
	int checkExit = 0;
	int StrPtx, StrPty;
	int  *startPointx = &StrPtx;
	int  *startPointy = &StrPty;
	//char **lab;
	fstream plik;
	plik.open("labirynt.txt", ios::in | ios::out);
	if (plik.good() == true)
	{

		plik >> xlab;
		plik >> ylab;

		int fragmentLabiryntu;

		char** lab = new  char*[xlab];
		for (int i = 0; i < xlab; ++i)
			lab[i] = new char[ylab];

		{

			for (int i = 0; i < xlab; i++)
			{
				for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
				{
					plik >> fragmentLabiryntu;
					switch (fragmentLabiryntu)
					{
					case 0:
						lab[i][j] = 32;
						break;
					case 1:
						lab[i][j] = 219;
						break;
					case 2:
						lab[i][j] = 176;
						break;
					case 3:
						lab[i][j] = 178;
						break;
					}
				}
			}

			cout << "xlab== " << xlab << endl;
			cout << "ylab== " << ylab << endl;

			botStart(xlab, ylab, lab, startPointx, startPointy);
			Printing(xlab, ylab,lab);
			do
			{
				botMove(xlab, ylab, lab);

			} while (checkExit != 0);
			
			
		}



		plik.close();
	}else //gdyby z jakiegoœ powodu plik zosta³ nieprawidlowo odczytany, lub nie odczytany w ogóle. (przypomne, ze plik ma sie nazywac labirynt.txt) 
	{
		cout << "Error! Blad odczytu pliku!" << endl;
		system("Pause");
		return 0;
	}
	system("Pause");


	//Lucas();
	return 0;
}


void Printing(int xlab, int ylab,char** lab)
{
	for (int i = 0; i < xlab; ++i, printf("\n"))
		for (int j = 0; j < ylab; ++j)
			cout << (char)lab[i][j];
}

void botStart(int xlab, int ylab, char** lab, int *startPointx, int *startPointy)
{
	int startx = -1, starty = -1;
	for (int i = 0; i < xlab; i++)
	{
		for (int j = 0; j < ylab; j++)
		{
			//cout << "lab[i][j]== " << (int)lab[i][j] << endl;
			if (lab[i][j] == -80)
			{
				startx = i;
				starty = j;
			}
		}
	}
	if (startx == -1 || starty == -1)
	{
		cout << "Error! Nie zanaleziono punktu Startu!" << endl;
	}
	else
	{
		lab[startx][starty] = 248;
	}
	*startPointx = startx;
	*startPointy = starty;
	//cout << "startPointx== " << *startPointx << endl;
	//cout << "startPointy== " << *startPointy << endl;
}

void botMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy)
{

}


void Lucas()
{
	int n0=2,n1=1,input=0;
	long long int n;

	cout << "wprowadz numer iczby lukasa, jaka chcesz otrzymac: ";
	cin >> input;
	cout << "twoja liczba to: " << input << endl;

	if (input == 0)
	{
		cout << "zerowa liczba Lucasa wynosi " << n0 << endl;
	}else if (input == 1) {
		cout << "pierwsza liczba lucasa wynosi " << n1 << endl;
	}
	else
		cout << input;
	do
	{
		n = n1 + n0;
		n0 = n1;
		n1 = n;
		input--;
	} while (input > 1);
	cout << " liczba Lucasa wynosi: " << n;
	system("Pause");
}

