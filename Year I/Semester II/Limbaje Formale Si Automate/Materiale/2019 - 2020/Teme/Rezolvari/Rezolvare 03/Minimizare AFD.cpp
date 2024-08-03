//
//  main.cpp
//  Minimalizare AFD
//
//  Created by Andrei Constantinescu on 23.04.2013.
//  Copyright (c) 2013 Andrei Constantinescu. All rights reserved.
//
// ALgoritmul folosit e acela de la seminar, cu matricea aia ciudata pe care o completezi pe jumatate
// Fisierele de intrare arata cam asa
//     Stari:
//     7
//     1 3
//     2 4
//     4 2
//     4 5
//     3 6
//     6 5
//     6 5
//  
//  
//     Finale:
//     5
//     6


#include "fstream"
#include "string.h"
#include "iostream"
using namespace std;

int stari[30][2], finale[30];
int nr_stari = 0, nr_fin = 0;

//citesti fisierele de input "minimizareAFD.in" - cel cu numarul de stari - si "finale.in" - cel cu starile finale ale automatului.
int citire_fisiere()
{
	char numefis[100] = "minimizareAFD.in";
	ifstream fis(numefis);
	if (fis.bad())
		cerr << "Eroare! Nu s-a putut deschide " << numefis << " pt citire";
	int i = 0;
	while (!fis.eof())
	{
		fis >> nr_stari;
		for(int i = 0; i < nr_stari; i++)
			for(int j = 0; j < 2; j++)
				fis >> stari[i][j];
	}
    
	char numefis1[100] = "finale.in";
	ifstream fis1(numefis1);
	if (fis1.bad())
		cerr << "Eroare! Nu s-a putut deschide " << numefis1 << " pt citire";
	i = 0;
	while (!fis1.eof())
	{
		fis1 >> finale[i];
		i++;
	}
	nr_fin = i;
	return 0;
}

//functia asta eeste folosita o singrua data pentru a verifica daca o stare apartine multimii de stari finale sau nu ...
bool apartine(int m[30], int x)
{
	bool gasit = false;
	for(int i = 0; i < nr_fin; i++)
		if(m[i] == x)
			gasit = true;
    
	return gasit;
}


int main()
{
	citire_fisiere();
	bool gasit = false;
	
	int n = nr_stari;
	char a[30][30];
	int h[30];
    
	for (int i = 0; i < n; i++)
		h[i] = 0; // vector ce retine daca starea trebuie eliminata sau nu
	h[0] = 1; // starea de instrare
    
	for (int i = 0; i < n; i++)// verific dak starile sunt accesibile sau nu si notez in h
	{
		if(stari[i][0] != -1) // -1 inseamna ca nu ma duce nicaieri
			h[stari[i][0]] = 1;
        
		if(stari[i][1] != -1)
			h[stari[i][1]] = 1;
	}
	

    
	for(int i = 0; i < n; i++) // elimin starile inaccesibile
		if(h[i] == 0)
	{
		stari[i][0] = -1;
		stari[i][1] = -1;
	}
    
	for (int i = 0; i < n; i++) // initializez matrice minimizare
		for(int j = 0; j < n; j++)
			a[i][j] = '-';
    
	for(int x = 0; x < nr_fin; x++) //marchez in matricea minimizare linia starilor finale
	{
		for(int i = 0; i < finale[x]; i++)
		{
			if(apartine(finale, i) == false)
				a[finale[x]][i] = '*';
		}
	}
    
	//********************************
	cout << "Matrice marcata doar cu starile finale:" << endl;
	for (int i = 0; i < n; i++) // afisare matrice minimizare
	{
		for(int j = 0; j < i; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	
	//********************************
	
	int a1, a2, b1, b2;
	gasit = true;
    
	
	// while-ul magic care face minimizarea verifica si marcheaza in toate perechile nemarcate pentru a le gasi pe cele echivalente, adica cele care la sfarsit sunt repr prin "-" in matricea a. 
	while(gasit == true) //marchez in matricea minimizare pana cand nu imi mai modifica nimic
	{
		gasit = false;
		for(int i = 0; i < n-1; i++)
		{
			for(int j = i+1; j< n; j++)
			{
				if(a[j][i] != '*')
				{
					a1 = stari[i][0];
					a2 = stari[j][0];
					b1 = stari[i][1];
					b2 = stari[j][1];
					
					if(a[a2][a1] == '*')
					{
						a[j][i] = '*';
						gasit = true;
					}
					
					if(a[b2][b1] == '*')
					{
						a[j][i] = '*';
						gasit = true;
					}
				}
			}
		}
	}
    
	cout << "\nMatrice:" << endl;
	for (int i = 0; i < n; i++) // afisare matrice minimizare
	{
		for(int j = 0; j < i; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
    
	// parcurg matricea din nou pentru a marca in vectorul h - care retine daca o stare trebuie eliminata sau nu - starile echivalente
	for (int i = 0; i < n; i++) // unde exista - in matricea minimizare atunci notez in h ca sunt eliminate
	{
		for(int j = 0; j < i; j++)
			if(a[i][j] == '-')
				h[i] = 0;
	}
    
	// afisez nodurile eliminate
	cout << endl << "Nodurile eliminate: " << endl << endl;
	for(int i = 0; i < n; i++)
		if(h[i] == 0)
			cout << "q" << i << endl;
	cout << endl;
    
	
	// afisez noul automat minimizat cu starile echivalente eliminate
	for (int i = 0; i < n; i++)
		if (h[i] == 1)
	{
		cout << "(" << i << ", 0) -> ";
		if(h[stari [i][0]] == 0)
			cout << stari[i][0] - 1<< endl;
		else
			cout << stari[i][0]<< endl;
            
		cout << "(" << i << ", 1) -> ";
		if(h[stari [i][1]] == 0)
			cout << stari[i][1] - 1<< endl;
		else
			cout << stari[i][1]<< endl;
	}
    
	return 0;
}
