#pragma once
#include "polinom.h"
#include "polinom_reductibil.h"
#include <iostream>
class polinom_reductibil;

class polinom_ireductibil : public polinom
{
public:
	polinom_ireductibil()  //constructor
	{
		nr_monoame = 0;
		m = new Monom[0];
	}
	polinom_ireductibil(int grad, float a[]) : polinom(grad, a)//constructor
	{}

	polinom_ireductibil(polinom_reductibil& ob); //constructor de conversie


	polinom_ireductibil(const polinom_ireductibil& ob); //copy constructor

	~polinom_ireductibil() //destructor
	{}

	void print_me(ostream& os);//pur virt in polinom
	void read_me(istream& os);//pur virtuala in polinom

	polinom_ireductibil& operator =(const polinom_ireductibil& ob);
};
