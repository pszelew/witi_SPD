

#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <string>
#include <list>
#include <queue> 

using namespace std;

struct zadanie
{
	int id; //id zadania
	int p; //czas trwania zadania
	int w; //waga zadania za spoznienie
	int d; //kiedy powinno sie zakonczyc
};

struct hist_elem
{
	int dlugosc;
	list<int> uszeregowanie;
};



int dlugosc_uszeregowania(int n, zadanie zadania[])
{
	int dlugosc = 0;
	for (int i = 0; i < n; i++)
	{
		dlugosc += zadania[i].p;
	}

	return dlugosc;
}

int C(int n_iter, zadanie zadania[]) //zwraca dlugosc uszeregowania dla kolejnej iteracji petli
{
	int dlugosc = 0;
	int i = 0;
	int temp = n_iter;
	if (temp == 0)
		return 0;
	//przelczenie iteracji na kod 0-1
	while(temp!=0)
	{
		if (temp % 2 == 1)
		{
			dlugosc += zadania[i].p;
		}

		temp = temp / 2;
		
		++i;

	}
	return dlugosc;
}

int K(int n_zadania, int time, zadanie zadania[])  //kara zadania n_zadania zakonczonego w czasie time
{

	

	if (time <= zadania[n_zadania].d)
		return 0;

	
	return(zadania[n_zadania].w*(time-zadania[n_zadania].d));
}


void F(int n_iter, zadanie zadania[], hist_elem historia[]) //zwraca optymalna kare 
{
	int kara_aktualna = INT_MAX;
	int kara_temp = 0;
	int i = 0;
	int temp = n_iter;
	int temp_2 = n_iter;
	int time = C(temp, zadania);

	list<int> uszeregowanie;

	//przeliczenie iteracji na kod 0-1

	if (n_iter == 0)
	{
		kara_aktualna = 0;
	}


	while (temp != 0)
	{
		if (temp % 2 == 1)
		{
			temp_2 -= pow(2, i); //odejmujemy wlasnie wykryte zadanie

			kara_temp = historia[temp_2].dlugosc + K(i, time, zadania);
			if(kara_aktualna > kara_temp) //zamieniamy miejscami
			{
				kara_aktualna = kara_temp;
				uszeregowanie = historia[temp_2].uszeregowanie;
				uszeregowanie.push_back(i);
			}
		}
		temp_2 = n_iter;
		temp = temp / 2;

		++i;
	}

	historia[n_iter].dlugosc = kara_aktualna;
	historia[n_iter].uszeregowanie = uszeregowanie;
	
}




hist_elem* opymalne_uszeregowanie(int n, zadanie zadania[])
{
	int num_iter = pow(2, n);

	hist_elem* historia = new hist_elem[num_iter];//tabela dynamiczna przechowująca informacje o naszych optymalnych karach w poprzednich krokach

	for (int i = 0; i < (num_iter); i++)
	{
		F(i, zadania, historia);
	}



	return historia;
}


int main()
{
	int n; //ile zadan mamy do uszeregowania

	zadanie tab[99]; //tutaj przechowujemy wczytane zadania

	hist_elem* historia;

	for (int g = 0; g < 11; g++)
	{
		ifstream data("data.txt");
		string s = "";
		string nazwa = "data." + to_string(g + 10) + ":";
		while (s != nazwa)
		{
			data >> s;
		}
		data >> n;

		int last_iteration_idx = int(pow(2, n)) - 1; //ostatni indeks w tablicy historii
		
		for (int i = 0; i < n; i++)
		{
			tab[i].id = i + 1; //przypisujemy id zaczynajac od id=1
			data >> tab[i].p; //wczytujemy informacje o p - czasie trwania
			data >> tab[i].w; //wczytujemy informacje o w - wadze kary za spoznienie
			data >> tab[i].d; //wczytujemy informacje o d - oczekiwanym terminie zakonczenia sie zadania
		}


		historia = opymalne_uszeregowanie(n, tab);

		cout << "Dlugosc optymalnego uszeregowania: " <<historia[last_iteration_idx].dlugosc<<endl;

		cout << "Kolejnosc uszeregowania:";
		for (list<int>::iterator it = historia[last_iteration_idx].uszeregowanie.begin(); it != historia[last_iteration_idx].uszeregowanie.end(); ++it)
			std::cout << ' ' << *it+1;
		cout << endl;


		/////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////
		
		/*Tutaj wypisujemy na probe nasze dane z tablicy*/
		/*
		for (int i = 0; i < n; i++)
		{
			cout << tab[i].p << " ";
			cout << tab[i].w << " ";
			cout << tab[i].d << " ";
			cout << endl;
		}
		*/
		
	}
	system("pause");

}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
