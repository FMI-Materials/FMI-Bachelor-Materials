#include<iostream>
#include "polinom.h"
#include "Monom.h"
#include "polinom_reductibil.h"
#include "polinom_ireductibil.h"
#include <vector>
using namespace std;

void citire(int& n, vector<polinom*>& P)
{
	int i;
	char optiune[100];

	//upcasting
	i = 0;
	while (i < n)
	{

		try
		{
			cout << "dati optiunea polinom R/I: ";
			cin.getline(optiune, 100);
			if (strcmp(optiune, "R") == 0 || strcmp(optiune, "I") == 0)
				throw optiune;
			else
				throw 0;
		}
		catch (char optiune[])
		{
			if (strcmp(optiune, "R") == 0)
			{
				polinom_reductibil* r = new polinom_reductibil;
				cin >> *r;
				cin.get();

				if ((*r).verific_ired() == 0)
				{
					//transform polinom red in ired
					cout << endl << "Nu e reductibil" << endl;
					polinom_ireductibil* i = new polinom_ireductibil(*r);//conversie
					P.push_back(i);
				}

				else
				{
					//incarc polinomul reductibil
					P.push_back(r);
					cout << "E reductibil se descompune:" << endl;
					//descompunere
					polinom_ireductibil r1, r2;
					int grad = (*r).get_nrm() - 1;
					(*r).descompun(grad, r1, r2);

					//afisez descompunerile
					cout << *r << "Se descompune in: " << endl;
					cout << r1;
					cout << r2;

				}

			}
			else
			{
				polinom_ireductibil* i = new polinom_ireductibil;
				cin >> *i;
				cin.get();

				P.push_back(i);

			}
			
			i++;
		
		}
		
		catch (int i)
		{
			
				cout << "NU AI ALES BINE!!" << endl;
		}


	}

}
void afisare(int n, vector<polinom*>P)
{

	cout << "cele n polinoame date sunt:" << endl;

	for (vector<polinom*>::iterator it = P.begin(); it != P.end(); it++)
		cout << **it;


}
int main()
{
	int n;
	
	cout << "Dati nr de polinoame n= ";
	cin >> n;
	cin.get();
	vector<polinom*>P;
	citire(n, P);
	afisare(n, P);
	//polinom reductibil de grad 3: X^3-3X-2=(x-2)(x^2+x+1)
						  //grad 3: X^3+4X^2-4X-1=(X-1)(X^2+5X+1)
	//polinom reductibil de grad 2: x^2-2X+1 = (x-1)(x-1)
	
	return 0;
	
}