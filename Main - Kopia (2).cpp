#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <Windows.h>

/*
UWAGA!!!
X sa zamienione z Y!!!
x-to wysokosc a y-to szerokosc

kiedys moze to naprawie.
(powstrzymuje smiech)

w ramach przypomnienia:

BOT = 248
SPACJA = 32
SCIANA = -37 (albo 219, zalezy co sprawdza)
P.STARTU / PRZEBYTA DROGA = 176
P.WYJSCIA = 178 (-78)
ROZGALEZIENIE = 254
*/



using namespace std;
int xlab, ylab;

int testExitx=-1;
int testExity=-1;
int ilRuchow = 0;
int crosswayLastMove=-1;
bool wDrugaStrone = false;

int Lucas(int n);

void Printing(int xlab, int ylab, char** lab);

void botStart(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, int *realStartPointx, int *realStartPointy, int *lastPositionx, int *lastPositiony);
int botMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int *ptrcrosswayPointx, int *ptrcrosswayPointy, int *realStartPointx, int *realStartPointy, int *lastPositionx, int *lastPositiony, char **wyniklab);

void BotRealMove(int xlab, int ylab, char** lab, int moveDirection, int *startPointx, int *startPointy, int *ptrcrosswayPointx, int *ptrcrosswayPointy, char **wyniklab);
void BotCrosswayMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int crosswayPointx, int crosswayPointy, char **wyniklab);
void BotBuildWall(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int crosswayPointx, int crosswayPointy);

void printExit(int xlab, int ylab, char** wyniklab);

int main()
{

	int checkExit = 0;
	int StrPtx, StrPty, rStrPtx, rStrPty;
	int *startPointx = &StrPtx;
	int *startPointy = &StrPty;
	int *realStartPointx = &rStrPtx;
	int *realStartPointy = &rStrPty;

	int test;

	//Punkt ostatniej pozycji(zeby bot sie nie cofal).
	int lstPosx, lstPosy;
	int *lastPositionx = &lstPosx;
	int *lastPositiony = &lstPosy;

	//boole wskazujace, czy dana strona jest dostepna, czy nie.
	bool avaNorth, avaWest, avaSouth, avaEast;
	bool *ptravaNorth = &avaNorth;
	bool *ptravaEast = &avaEast;
	bool *ptravaSouth = &avaSouth;
	bool *ptravaWest = &avaWest;

	//punkt rozdroża.
	int crosswayPointx = -1, crosswayPointy = -1;
	int *ptrcrosswayPointx = &crosswayPointx;
	int *ptrcrosswayPointy = &crosswayPointy;

	//char **lab;
	fstream plik;
	plik.open("labirynt1.txt", ios::in | ios::out);
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




					char** orginalLab = new  char*[xlab];
		for (int i = 0; i < xlab; ++i)
			orginalLab[i] = new char[ylab];
		{

			for (int i = 0; i < xlab; i++)
			{
				for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
				{
					orginalLab[i][j] = lab[i][j];
				}
			}
		}





			char** wyniklab = new  char*[xlab];
			for (int i = 0; i < xlab; ++i)
				wyniklab[i] = new char[ylab];
			{

				for (int i = 0; i < xlab; i++)
				{
					for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
					{
						wyniklab[i][j] = lab[i][j];
					}
				}
			}





			//cout << "xlab== " << xlab << endl;
			//cout << "ylab== " << ylab << endl;

			Printing(xlab, ylab, lab);
			botStart(xlab, ylab, lab, startPointx, startPointy, realStartPointx, realStartPointy, lastPositionx, lastPositiony);
			Printing(xlab, ylab, lab);
			do
			{
				checkExit = botMove(xlab, ylab, lab, startPointx, startPointy, ptravaNorth, ptravaEast, ptravaSouth, ptravaWest, ptrcrosswayPointx, ptrcrosswayPointy, realStartPointx, realStartPointy, lastPositionx, lastPositiony, wyniklab);
				Printing(xlab, ylab, lab);

			} while (checkExit == 0);

			if (checkExit == 1)
			{
				checkExit = 0;
				wDrugaStrone = true;
				printExit(xlab, ylab, wyniklab);
				cout << endl << endl << "botowi udalo sie wyjsc z labiryntu!" << endl << endl;
				cout << "Ilosc wykonanych ruchow: " << ilRuchow << endl;
				ilRuchow = 0;

				//lab[*startPointx][*startPointy] == 32;
				*startPointx = *realStartPointx;
				*startPointy = *realStartPointy;

				for (int i = 0; i < xlab; i++)
				{
					for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
					{
						lab[i][j] = orginalLab[i][j];
					}
				}

				for (int i = 0; i < xlab; i++)
				{
					for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
					{
						wyniklab[i][j] = orginalLab[i][j];
					}
				}

				do // I sprawdzenie w druga strone
				{
					//cout << "Program wszedl do funkcji odwracajacej kolejknosc sprawdzania" << endl;
					checkExit = botMove(xlab, ylab, lab, startPointx, startPointy, ptravaNorth, ptravaEast, ptravaSouth, ptravaWest, ptrcrosswayPointx, ptrcrosswayPointy, realStartPointx, realStartPointy, lastPositionx, lastPositiony, wyniklab);
					Printing(xlab, ylab, lab);
					//system("pause");

				} while (checkExit == 0);
				if (checkExit == 1)
				{

					printExit(xlab, ylab, wyniklab);
					cout << endl << endl << "botowi udalo sie wyjsc z labiryntu!" << endl << endl;
					cout << "Ilosc wykonanych ruchow: " << ilRuchow << endl;
				}


				fstream wynik;
				wynik.open("wynik.txt", ios::in | ios::out);
				if (wynik.good() == true)
				{


					for (int i = 0; i < xlab; i++)
					{
						for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
						{
							switch (wyniklab[i][j])
							{
							case 32:
								wyniklab[i][j] = 0;
								break;
							case -37:
								wyniklab[i][j] = 1;
								break;
							case -80:
								wyniklab[i][j] = 2;
								break;
							case -78:
								wyniklab[i][j] = 3;
								break;
							}
						}
					}


					wynik << xlab << "\n";
					wynik << ylab << "\n";
					for (int i = 0; i < xlab; i++)
					{
						for (int j = 0; j < ylab; ++j) //wpisanie wartosci do tablicy
						{
							wynik << (int)wyniklab[i][j];
						}
						wynik << "\n";
					}
					system("pause");
					wynik.close();
				}
				else {
					cout << "blad odczytu pliku wynikowego!" << endl;
					system("Pause");
					return -1;
				}

				

			}
			else
			{
				cout << "wystapil nieoczekiwany blad";
			}

		}



		plik.close();
	}
	else //gdyby z jakiegoś powodu plik został nieprawidlowo odczytany, lub nie odczytany w ogóle. (przypomne, ze plik ma sie nazywac labirynt.txt) 
	{
		cout << "Error! Blad odczytu pliku!" << endl;
		system("Pause");
		return 0;
	}
	system("Pause");


	{
		int luc;
		cout << "Podaj liczbe Lucasa" << endl;
		cin >> luc;
		cout << Lucas(luc);
		system("Pause");
	}

	return 0;
}


void Printing(int xlab, int ylab, char** lab)
{
	for (int i = 0; i < xlab; ++i, printf("\n"))
		for (int j = 0; j < ylab; ++j)
			cout << (char)lab[i][j];
	Sleep(100);
	//system("Pause");
	system("cls");
}

void printExit(int xlab, int ylab, char** wyniklab)
{
	for (int i = 0; i < xlab; ++i, printf("\n"))
		for (int j = 0; j < ylab; ++j)
			cout << (char)wyniklab[i][j];
	system("Pause");
	system("cls");
}

void botStart(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, int *realStartPointx, int *realStartPointy, int *lastPositionx, int *lastPositiony)
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
	*realStartPointx = startx;
	*realStartPointy = starty;
	*lastPositionx = startx;
	*lastPositiony = starty;
}

int botMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int *ptrcrosswayPointx, int *ptrcrosswayPointy, int *realStartPointx, int *realStartPointy, int *lastPositionx,int *lastPositiony,char **wyniklab)
{
	*ptravaNorth = false;
	*ptravaEast = false;
	*ptravaSouth = false;
	*ptravaWest = false;

	int avaMoves = 0;
	int moveDirection = 0;
	int testx, testy;
	testx = xlab;
	testy = ylab;

	int PstartPointx, PstartPointy;
	PstartPointx = *startPointx;
	PstartPointy = *startPointy;


	if (*startPointx == testExitx && *startPointy == testExity)
	{
		return 1;
	}


	/*
	
	moveDirection cheatSheat:
		1 = North
		2 = South
		3 = West
		4 = East
	
	*/

	//cout << "lastPositionx = " << *lastPositionx << " lastPositiony = " << *lastPositiony << endl;
	//cout << "avaMoves(w tym miejscu ma wynosic zero)= " << avaMoves << endl;
	if (wDrugaStrone == false)
	{
		if (*startPointx - 1 >= 0)
		{
			if (lab[*startPointx - 1][*startPointy] == 32 || lab[*startPointx - 1][*startPointy] == -78)
			{
				if (*lastPositionx != *startPointx - 1)
				{
					if (lab[*startPointx - 1][*startPointy] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaNorth = true;
					avaMoves += 1;
					moveDirection = 1;
				}
				else { //cout << "bot przyszedl z polnocy." << endl;
				}
			}
			else { //cout << endl << "brak mozliwosci ruchu w kierunku polnocnym."<< endl;
			}
		}
		else { //cout << "startPointx - 1 NIE jest wieksze rowne 0" << endl;
		}
		//cout << "avaMoves(north)= " << avaMoves << endl;
		if (*startPointx + 1 <= xlab)
		{
			if (lab[*startPointx + 1][*startPointy] == 32 || lab[*startPointx + 1][*startPointy] == -78)
			{
				if (*lastPositionx != *startPointx + 1)
				{
					if (lab[*startPointx + 1][*startPointy] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaSouth = true;
					avaMoves += 1;
					moveDirection = 2;
				}
				else {// cout << "bot przyszedl z polodnia." << endl;
				}
			}
			else { //cout << endl << "brak mozliwosci ruchu w kierunku poludniowym." << endl;
			}
		}
		else { //cout << "startPointx + 1 NIE jest mniejsze rowne xlab" << endl;;
		}
		//cout << "avaMoves(south)= " << avaMoves << endl;
		if (*startPointy - 1 >= 0)
		{
			if (lab[*startPointx][*startPointy - 1] == 32 || lab[*startPointx][*startPointy - 1] == -78)
			{
				if (*lastPositiony != *startPointy - 1)
				{
					if (lab[*startPointx][*startPointy - 1] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaWest = true;
					avaMoves += 1;
					moveDirection = 3;
				}
				else {// cout << "bot przyszedl z zachodu." << endl; 
				}
			}
			else {// cout << endl << "brak mozliwosci ruchu w kierunku zachodnim." << endl;
			}
		}
		else {// cout << "startPointy - 1 NIE jest wieksze rowne 0" << endl;
		}
		//cout << "avaMoves(west)= " << avaMoves << endl;
		if (*startPointy + 1 <= ylab)
		{
			if (lab[*startPointx][*startPointy + 1] == 32 || lab[*startPointx][*startPointy + 1] == -78)
			{
				if (*lastPositiony != *startPointy + 1)
				{
					if (lab[*startPointx][*startPointy + 1] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaEast = true;
					avaMoves += 1;
					moveDirection = 4;
				}
				else {// cout << "bot przyszedl z wschodu." << endl;
				}
			}
			else { //cout << endl <<  "brak mozliwosci ruchu w kierunku wschodnim."<< endl;
			}
		}
		else { //cout << "startPointy + 1 NIE jest mniejsze rowne ylab" << endl;
		}
	}
	else
	{
		if (*startPointy + 1 <= ylab)
		{
			if (lab[*startPointx][*startPointy + 1] == 32 || lab[*startPointx][*startPointy + 1] == -78)
			{
				if (*lastPositiony != *startPointy + 1)
				{
					if (lab[*startPointx][*startPointy + 1] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaEast = true;
					avaMoves += 1;
					moveDirection = 4;
				}
				else {// cout << "bot przyszedl z wschodu." << endl;
				}
			}
			else { //cout << endl <<  "brak mozliwosci ruchu w kierunku wschodnim."<< endl;
			}
		}
		else { //cout << "startPointy + 1 NIE jest mniejsze rowne ylab" << endl;
		}

		if (*startPointy - 1 >= 0)
		{
			if (lab[*startPointx][*startPointy - 1] == 32 || lab[*startPointx][*startPointy - 1] == -78)
			{
				if (*lastPositiony != *startPointy - 1)
				{
					if (lab[*startPointx][*startPointy - 1] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaWest = true;
					avaMoves += 1;
					moveDirection = 3;
				}
				else {// cout << "bot przyszedl z zachodu." << endl; 
				}
			}
			else {// cout << endl << "brak mozliwosci ruchu w kierunku zachodnim." << endl;
			}
		}
		else {// cout << "startPointy - 1 NIE jest wieksze rowne 0" << endl;
		}

		if (*startPointx + 1 <= xlab)
		{
			if (lab[*startPointx + 1][*startPointy] == 32 || lab[*startPointx + 1][*startPointy] == -78)
			{
				if (*lastPositionx != *startPointx + 1)
				{
					if (lab[*startPointx + 1][*startPointy] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaSouth = true;
					avaMoves += 1;
					moveDirection = 2;
				}
				else {// cout << "bot przyszedl z polodnia." << endl;
				}
			}
			else { //cout << endl << "brak mozliwosci ruchu w kierunku poludniowym." << endl;
			}
		}
		else { //cout << "startPointx + 1 NIE jest mniejsze rowne xlab" << endl;;
		}

		if (*startPointx - 1 >= 0)
		{
			if (lab[*startPointx - 1][*startPointy] == 32 || lab[*startPointx - 1][*startPointy] == -78)
			{
				if (*lastPositionx != *startPointx - 1)
				{
					if (lab[*startPointx - 1][*startPointy] == -78)
					{
						wyniklab[*startPointx][*startPointy] = 176;
						cout << "Bot znalazl wyjscie z labiryntu!" << endl;
						return 1;
					}
					*ptravaNorth = true;
					avaMoves += 1;
					moveDirection = 1;
				}
				else { //cout << "bot przyszedl z polnocy." << endl;
				}
			}
			else { //cout << endl << "brak mozliwosci ruchu w kierunku polnocnym."<< endl;
			}
		}
		else { //cout << "startPointx - 1 NIE jest wieksze rowne 0" << endl;
		}
	}


	*lastPositionx = *startPointx;
	*lastPositiony = *startPointy;

	
	//cout << "wyjacie jest oznaczone numerem: "<<(int)lab[5][4]<<endl;
	//cout << "startPointx= " << *startPointx << endl <<"startPointy= "<< *startPointy << endl << endl;
	//cout << endl << "(int)lab[1][1]= " << (int)lab[1][1] << endl;
	//cout <<"xlab= "<< xlab <<" ylab= "<< ylab << endl;
	//cout << "testx (z botMove)= " << testx << endl <<"testy (z botMove)= "<< testy << endl;
	//cout << "avaMoves(East + rest)= " << avaMoves << endl;
	//cout << "crosswayPointx= " << *ptrcrosswayPointx << " crosswayPointy= " << *ptrcrosswayPointy << endl;
	//cout << "rozgalezienie= "<<(int)lab[2][3] << endl;


	//system("Pause");
	if (avaMoves == 0) {
		//cout << "ERROR!!! brak mozliwosci ruchu!!!" << endl;
		//cout << "Powrot do ostatniego punktu rozwidlenia drog." << endl;
		cout << "Powrot do punktu startu." << endl;
		if (*ptrcrosswayPointx == -1 || *ptrcrosswayPointy == -1) 
		{
			cout << "ERROR!!! po drodze nie znaleziono zadnego punktu rozgalezinia. Powtarzanie labiryntu nie ma sensu!" << endl;
			//cout << "Konczenie dzialania programu." << endl;
			return -1;
		}
		else 
		{
			ilRuchow++;
			int startx = -1, starty = -1;
			for (int i = 0; i < xlab; i++)
			{
				for (int j = 0; j < ylab; j++)
				{
					//cout << "lab[i][j]== " << (int)lab[i][j] << endl;
					if (lab[i][j] == -2)
					{
						lab[i][j] = 32;
					}
				}
			}
			lab[*startPointx][*startPointy] = 219;
			wyniklab[*startPointx][*startPointy] = 176;
			*startPointx = *realStartPointx;
			*startPointy = *realStartPointy;
			lab[*startPointx][*startPointy] = 248;
			BotBuildWall(xlab, ylab, lab, startPointx, startPointy, ptravaNorth, ptravaEast, ptravaSouth, ptravaWest, *ptrcrosswayPointx, *ptrcrosswayPointy);
		}
		
	}
	else if (avaMoves == 1)
	{
		ilRuchow++;
		BotRealMove(xlab,ylab,lab,moveDirection,startPointx,startPointy, ptrcrosswayPointx, ptrcrosswayPointy,wyniklab);
	}
	else if (avaMoves > 1)
	{
		ilRuchow++;
		*ptrcrosswayPointx = *startPointx;
		*ptrcrosswayPointy = *startPointy;
		//cout << "crosswayPointx= " << *ptrcrosswayPointx << " crosswayPointy= " << *ptrcrosswayPointy << endl;
		BotCrosswayMove(xlab, ylab, lab, startPointx, startPointy, ptravaNorth, ptravaEast, ptravaSouth, ptravaWest, *ptrcrosswayPointx, *ptrcrosswayPointy, wyniklab);
	}
	else 
	{
		cout << "ERROR!!! nieznany Blad w funkcji botMove!!! " << endl;
		return -1;
	}
	//testExitx = *startPointx;
	//testExity = *startPointy;


	return 0;
}

void BotRealMove(int xlab, int ylab, char** lab,int moveDirection, int *startPointx, int *startPointy, int *ptrcrosswayPointx, int *ptrcrosswayPointy,char **wyniklab)
{
	int testx=*startPointx, testy=*startPointy;

	wyniklab[*startPointx][*startPointy] = 176;
	lab[*startPointx][*startPointy] = 32;

	//cout << " startPointx= " << *startPointx << " startPointy= " << *startPointy << endl;
		if (wDrugaStrone == false)
		{
			switch (moveDirection)
			{
			case 1:
				//cout << "North"<<endl;
				testx = *startPointx;
				testx--;
				break;
			case 2:
				//cout << "South" << endl;
				testx = *startPointx;
				testx++;
				break;
			case 3:
				//cout << "West" << endl;
				testy = *startPointy;
				testy--;
				break;
			case 4:
				//cout << "East" << endl;
				testy = *startPointy;
				testy++;
				break;
			}
		}
		else 
		{
			switch (moveDirection)
			{
			case 4:
				//cout << "North"<<endl;
				testy = *startPointy;
				testy++;
				break;
			case 3:
				//cout << "South" << endl;
				testy = *startPointy;
				testy--;
				break;
			case 2:
				//cout << "West" << endl;
				testx = *startPointx;
				testx++;
				break;
			case 1:
				//cout << "East" << endl;
				testx = *startPointx;
				testx--;
				break;
			}
		}





		if (*ptrcrosswayPointx == testx && *ptrcrosswayPointy == testy)
		{
			//lab[*startPointx][*startPointy] = 219;
		}
		//cout << " startPointx= " << *startPointx << " startPointy= " << *startPointy << endl;
		//cout << " testx= " << testx << " testy= " << testy << endl;


			lab[testx][testy] = 248;

			

			*startPointx = testx;
			*startPointy = testy;

			
}

void BotCrosswayMove(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int crosswayPointx, int crosswayPointy, char **wyniklab)
{
	int testx, testy;
	testx = *startPointx;
	testy = *startPointy;

	lab[*startPointx][*startPointy] = 254;
	wyniklab[*startPointx][*startPointy] = 176;
	if (wDrugaStrone == false)
	{
		if (*ptravaNorth == true)
		{
			testx--;
			crosswayLastMove = 0;
		}
		else if (*ptravaSouth == true)
		{
			testx++;
			crosswayLastMove = 1;
		}
		else if (*ptravaWest == true)
		{
			testy--;
			crosswayLastMove = 2;
		}
		else if (*ptravaEast == true)
		{
			testy++;
			crosswayLastMove = 3;
		}
	}
	else 
	{
		if (*ptravaEast == true)
		{
			testy++;
			crosswayLastMove = 3;
		}
		else if (*ptravaWest == true)
		{
			testy--;
			crosswayLastMove = 2;
		}
		else if (*ptravaSouth == true)
		{
			testx++;
			crosswayLastMove = 1;
		}
		else if (*ptravaNorth == true)
		{
			testx--;
			crosswayLastMove = 0;
		}
	}

	*startPointx = testx;
	*startPointy = testy;
	lab[*startPointx][*startPointy] = 248;
	
}

void BotBuildWall(int xlab, int ylab, char** lab, int *startPointx, int *startPointy, bool *ptravaNorth, bool *ptravaEast, bool *ptravaSouth, bool *ptravaWest, int crosswayPointx, int crosswayPointy)
{
	int testx, testy;
	testx = crosswayPointx;
	testy = crosswayPointy;
	if (wDrugaStrone == false)
	{
		if (crosswayLastMove == 0)
		{
			testx--;
		}
		else if (crosswayLastMove == 1)
		{
			testx++;
		}
		else if (crosswayLastMove == 2)
		{
			testy--;
		}
		else if (crosswayLastMove == 3)
		{
			testy++;
		}
	}
	else 
	{
		if (crosswayLastMove == 3)
		{
			testy++;
		}
		else if (crosswayLastMove == 2)
		{
			testy--;
		}
		else if (crosswayLastMove == 1)
		{
			testx++;
		}
		else if (crosswayLastMove == 0)
		{
			testx--;
		}
	}



	lab[testx][testy] = 219;
}

int Lucas(int n)
{


	if (n == 1)return 2;
	if (n == 2)return 1;
	else return Lucas(n - 2) + Lucas(n - 1);

}



















/*
	UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! UWAGA!!! 

	Rzeczy, ktore moga sie przydac, ale prawdopodobnie sie nie przydaca.
*/

//cos z botMove

/*

if (*startPointx-1 <0)
{
cout << "ruch w strone polnocy spowodowalby wyjscie poza plansze.";
ptravaNorth = false;
}


if (*startPointx + 1 > ylab)
{
cout << "ruch w strone poludnia spowodowalby wyjscie poza plansze.";
ptravaSouth = false;
}


if (*startPointy - 1 <0)
{
cout << "ruch w strone wschodu spowodowalby wyjscie poza plansze.";
ptravaEast = false;
}


if (*startPointy + 1 > ylab)
{
cout << "ruch w strone zachodu spowodowalby wyjscie poza plansze.";
ptravaWest = false;
}

*/

//Lucas

/*
int n0 = 2, n1 = 1, input = 0;
long long int n;
cout << "wprowadz numer iczby lukasa, jaka chcesz otrzymac: ";
cin >> input;
cout << "twoja liczba to: " << input << endl;
if (input == 0)
{
cout << "zerowa liczba Lucasa wynosi " << n0 << endl;
}
else if (input == 1) {
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
*/