#include "Monom.h"
ostream& operator <<(ostream& os, Monom& ob)
{
	os << "Ati dat monomul:";
	if (ob.coef == 0)
		os << 0;
	else
	{
		if (ob.coef == 1)
		{
			if (ob.grad == 0)
				os << 1;
			else
				os << "x^" << ob.grad;
		}
		else
		{

			if (ob.grad == 0)
				os << ob.coef;
			else
				os << ob.coef << "x^" << ob.grad;
		}

	}
	os << endl;
	return os;
}
istream& operator >>(istream& os, Monom& ob)
{
	cout << "Dati un monom:(grad, coef) " << endl;
	os >> ob.grad;
	os >> ob.coef;
	return os;
}
Monom& Monom:: operator =(const Monom& ob)
{

	grad = ob.grad;
	coef = ob.coef;
	return *this;
}
