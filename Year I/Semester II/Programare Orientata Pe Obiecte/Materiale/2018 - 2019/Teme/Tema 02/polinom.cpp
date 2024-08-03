#include "polinom.h"

polinom& polinom :: operator =(const polinom& ob)
{
	nr_monoame = ob.nr_monoame;

	m = new Monom[nr_monoame];
	int i;
	for (i = 0; i < nr_monoame; i++)
		m[i] = ob.m[i];
	return *this;

}

ostream& operator << (ostream& os, polinom& ob)
{
	ob.print_me(os);
	return os;

}
istream& operator >> (istream& os, polinom& ob)
{
	ob.read_me(os);
	return os;
}
polinom::polinom(const polinom& ob)//copy constructor
{
	nr_monoame = ob.nr_monoame;
	int i;
	m = new Monom[nr_monoame];
	for (i = 0; i < nr_monoame; i++)
		m[i] = ob.m[i];
}
void polinom::set_pol(int grad, float a[])
{
	//grad n => n+1 monoame/coeficienti
	//incep de la a0 x^0, a1 x^1, ....an x^n
	nr_monoame = grad + 1;

	m = new Monom[grad + 1];
	int i;
	for (i = 0; i <= grad; i++)
		m[i].set(i, a[i]);


}
