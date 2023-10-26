#pragma once
#include<iostream>
using namespace std;
class Monom
{
	int grad;
	float coef;
public:
	Monom() //constructor
	{
		grad = 0;
		coef = 0;
	}
	Monom(int g, float c)//constructor cu parametrii
	{
		set(g, c);
	}
	Monom(const Monom& ob) //copy constructor
	{
		grad = ob.grad;
		coef = ob.coef;
	}
	~Monom() //destructor 
	{

		coef = 0;
		grad = 0;

	}
	int get_grad() //getter
	{
		return grad;
	}
	float get_coef() //getter
	{
		return coef;
	}
	void set(int g, float c) //setter
	{
		grad = g;
		coef = c;
	}
	friend ostream& operator <<(ostream& os, Monom& ob);
	friend istream& operator >>(istream& os, Monom& ob);
	Monom& operator =(const Monom& ob);
};
