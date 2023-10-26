#include "polinom_reductibil.h"

polinom_reductibil& polinom_reductibil:: operator =(const polinom_reductibil& ob)
{

	nr_monoame = ob.nr_monoame;
	int i;
	m = new Monom[ob.nr_monoame];
	for (i = 0; i < ob.nr_monoame; i++)
		m[i] = ob.m[i];

	return *this;

}

void polinom_reductibil::print_me(ostream& os)
{
	os << "Polinom reductibil: ";
	int i, c, g;
	for (i = 0; i < nr_monoame; i++)
	{

		c = int(m[i].get_coef());
		g = int(m[i].get_grad());

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
void polinom_reductibil::read_me(istream& os)
{
	cout << "dati polinomul REDUCTIBIL P(x): " << endl;
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
polinom_reductibil::polinom_reductibil(const polinom_reductibil& ob)
{
	nr_monoame = ob.nr_monoame;
	int i;
	for (i = 0; i < nr_monoame; i++)
		m[i] = ob.m[i];
}
bool polinom_reductibil::verific_coef()
{
	int i;
	for (i = 0; i < nr_monoame; i++)
		if (int(m[i].get_coef()) != float(m[i].get_coef()))
			return false;

	return true;
}
int cmmdc(int a, int b) //globala nu are treaba cu functia 
{
	while (a != b)
		if (a > b)
			a = a - b;
		else
			b = b - a;
	return a;
}
bool prim(int x) //globala verific daca e nr prim 
{
	int d;
	if (x == 1 || x == -1 || x == 0)
		return false;
	for (d = 2; d <= x / 2; d++)
		if (x % d == 0)
			return false;
	return true;
}

int polinom_reductibil::verific_ired()
{
	//verific daca un polinom este ireductibil

	
	if (verific_coef() == false)//daca coef nu sunt intregi => polinom ired
		return 0;
	
	int cm, i,nr;
	int grad;
	grad = get_nrm() - 1;
	//calculez cmmdc al coeficientilor
	cm = abs(m[0].get_coef());
	
	for (i = 1; i < nr_monoame; i++)
	{
		nr = abs(m[i].get_coef());
		if(nr!=0)
			cm = cmmdc(cm, nr);
	}
	
	//retin intr-un vector coeficientii primi :

	int pr[100], k = 0;
	
	for (i = 0; i < nr_monoame; i++)
		if (prim(m[i].get_coef()) == true)
			pr[k++] = m[i].get_coef();
	
	int j, p, x;
	if (cm == 1) //cmmdc coeficienti =1
	{
		
		//pot sa trec la criteriul lui Eisenstein
		for (i = 0; i < k; i++)
		{

			p = pr[i];
			for (j = 0; j < nr_monoame - 1; j++)
			{
				x = m[j].get_coef();


				if (x % p != 0) //primii n-1 coef trebuie sa divida p nr prim
					return grad;
			}
			x = m[nr_monoame - 1].get_coef();
		
			if (x % p == 0)// al n-lea coeficient nu trebuie sa divida p nr prim
				return grad;
			
			//p^2 nu trebuie sa divida primul coeficient
			x = m[0].get_coef();

			if (x % (p * p) == 0)
				return grad;

		}

	}
	return 0;

}

void polinom_reductibil::descompun(int grad, polinom_ireductibil& r1, polinom_ireductibil& r2)
{
	if (grad == 2)
	{


		int delta;
		int a0, a1, a2;

		a0 = m[0].get_coef();
		a1 = m[1].get_coef();
		a2 = m[2].get_coef();

		delta = a1 * a1 - 4 * a0 * a2;
		//polinom reductibil => are solutii reale => nu mai discut cazul cu delta<0

		float rad1, rad2;
		rad1 = (-a1 + sqrt(delta)) / 2 * a2;
		rad2 = (-a1 - sqrt(delta)) / 2 * a2;

		//descompunerea
		//constructorul de conversie =>primeste pol red si l face ired 
		float v1[2], v2[2];

		v1[0] = -1 * rad1;
		v1[1] = 1;
		v2[0] = a2 * -1 * rad2;
		v2[1] = a2;


		polinom_ireductibil A(1, v1), B(1, v2);

		r1 = A;
		r2 = B;


	}

	if (grad == 3)
	{

		//float p, q, P, Q;
		int a0, a1, a2, a3;

		a0 = m[0].get_coef();
		a1 = m[1].get_coef();
		a2 = m[2].get_coef();
		a3 = m[3].get_coef();
		
		int d, D, x1=0;
		//radacinile se afla printre divizorii lui a0/a3
		
		for (d = 1; d <= abs(a0 / a3) && x1 == 0; d++)
		
			if ((a3 * d * d * d + a2 * d *d +a1 * d + a0) == 0)
				x1 = d;

			else
			{
				D = -1 * d;

				if ((a3 * D * D * D + a2 * D *D +a1 * D + a0) == 0)
					x1 = D;


			}
		
		
		//din viete 
		float P, s;
		P = a1 / a3 - x1 * (-a2 / a3 - x1);
		s =-1*( -a2 / a3 - x1);
		float v1[2], v2[3];

		v1[0] = a3 * -1 * x1;
		v1[1] = a3;
		v2[0] = P;
		v2[1] = s;
		v2[2] = 1;

		polinom_ireductibil A(1, v1), B(2, v2);
		r1 = A;
		r2 = B;

		/*
		p = a1 / a3 - (a2 * a2) / (3 * a3 * a3);
		q = (2 * a2 * a2 * a2) / (27 * a3 * a3 * a3) - (a2 * a1) / (3 * a3 * a3) + a0 / a3;
		P = pow(-q / a3 + sqrt(p * p / 9 + q * q / 4), 1 / 3);
		Q = pow(-q / a3 - sqrt(p * p / 9 + q * q / 4), 1 / 3);

		float rad1, b, c;

		rad1 = P + Q;
		c = rad1 * rad1 / 4 + (P - Q) * (P - Q) * 3 / 4;
		b = rad1;
		cout << "rad1" << rad1 << endl;
		cout << "c,b" << c << " " << b << endl;
		float v1[2], v2[3];

		v1[0] = a3 * -1 * rad1;
		v1[1] = a3;
		v2[0] = c;
		v2[1] = b;
		v2[2] = 1;

		polinom_ireductibil A(1, v1), B(2, v2);
		r1 = A;
		r2 = B;
		*/


	}

}
