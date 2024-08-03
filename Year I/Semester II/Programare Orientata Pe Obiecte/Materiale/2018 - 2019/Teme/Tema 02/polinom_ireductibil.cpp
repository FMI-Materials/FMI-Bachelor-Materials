#include "polinom_ireductibil.h"

polinom_ireductibil::polinom_ireductibil(polinom_reductibil& ob)
{
	nr_monoame = ob.get_nrm();
	float* a;
	a = new float[nr_monoame];
	int i;
	for (i = 0; i < nr_monoame; i++)
		a[i] = ob.get_coef_pol(i);
	this->set_pol(nr_monoame - 1, a);

}

polinom_ireductibil& polinom_ireductibil:: operator =(const polinom_ireductibil& ob)
{

	nr_monoame = ob.nr_monoame;
	int i;
	m = new Monom[ob.nr_monoame];
	for (i = 0; i < ob.nr_monoame; i++)
		m[i] = ob.m[i];

	return *this;

}

polinom_ireductibil::polinom_ireductibil(const polinom_ireductibil& ob)
{
	nr_monoame = ob.nr_monoame;
	int i;
	for (i = 0; i < nr_monoame; i++)
		m[i] = ob.m[i];
}

void polinom_ireductibil::print_me(ostream& os)
{

	os << "Polinom ireductibil: ";
	int i;
	float c, g;
	for (i = 0; i < nr_monoame; i++)
	{

		c = m[i].get_coef();
		g = m[i].get_grad();

		if (i == 0 && c != 0)
		{
			os << c;
		}
		else
		{

			if (c < 0)
			{

				if (c == -1)
				{
					if (g != 0)
						os << "-x^" << g;
					else
						os << c;
				}
				else
				{

					if (g == 0)
						os << c;
					else
						os << c << "x^" << g;
				}
			}
			else
				if (c > 0)
				{
					if (c == 1)
					{
						if (g != 0)
							os << "+x^" << g;
					}
					else
					{
						os << "+";
						if (g == 0)
							os << c;
						else
							os << c << "x^" << g;
					}
				}
		}

	}
	os << endl;
}
void polinom_ireductibil::read_me(istream& os)
{
	cout << "dati polinomul IREDUCTIBIL P(x): " << endl;
	cout << "grad(p(x))= ";
	int grad;

	os >> grad;
	nr_monoame = grad + 1;
	m = new Monom[grad + 1];


	cout << "coeficientii polinomului a0,a1,...an sunt:" << endl;
	int i, x;
	for (i = 0; i <= grad; i++)
	{
		os >> x;
		m[i].set(i, x);

	}

}
