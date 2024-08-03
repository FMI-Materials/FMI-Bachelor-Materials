#pragma once
#include "Monom.h"
#include <iostream>
using namespace std;

class polinom //clasa abstracta
{
protected:
	int nr_monoame;
	Monom* m;
public:
	polinom() //constructor
	{
		nr_monoame = 0;
		m = new Monom;
	}
	polinom(int grad, float a[])//constructor 
	{
		set_pol(grad, a);
	}


	polinom(const polinom& ob); //copy constructor

	virtual ~polinom() //destructor
	{
		delete[]m;
		nr_monoame = 0;

	}
	void set_pol(int grad, float a[]);

	int get_nrm()
	{
		return nr_monoame;
	}
	float get_coef_pol(int i)
	{
		return m[i].get_coef();
	}
	int get_grad_pol(int i)
	{
		return m[i].get_grad();
	}


	virtual void print_me(ostream& os) = 0;// pur virtuala=>clasa abstracta
	virtual void read_me(istream& os) = 0;// pur virtuala

	friend istream& operator >> (istream& os, polinom& ob);//nu e virtuala
	friend ostream& operator << (ostream& os, polinom& ob);//nu e virtuala

	virtual polinom& operator =(const polinom& ob);

};
