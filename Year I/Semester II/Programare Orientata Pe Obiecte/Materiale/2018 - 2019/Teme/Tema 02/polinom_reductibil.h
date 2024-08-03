#pragma once
#include "polinom.h"
#include<iostream>
#include "polinom_ireductibil.h"
using namespace std;

class polinom_ireductibil;

class polinom_reductibil : public polinom
{
public:
	polinom_reductibil() //constrcutor 
	{
		nr_monoame = 0;
		m = new Monom[0];
	}

	polinom_reductibil(int grad, float a[]) : polinom(grad, a)//constructor
	{}

	polinom_reductibil(const polinom_reductibil& ob); //copy constructor

	~polinom_reductibil() //destructor
	{}

	void print_me(ostream& os);//pur virtuala in polinom
	void read_me(istream& os);//pur virtuala in polinom

	polinom_reductibil& operator =(const polinom_reductibil& ob);


	int verific_ired();//folosesc criteriul returnez 0 daca e ired, 2/3 grad pt pol red 
	bool verific_coef();//verific daca coef sunt intregi=>pol posibil reductibil

	//descompunere
	void descompun(int grad, polinom_ireductibil& r1, polinom_ireductibil& r2);



};