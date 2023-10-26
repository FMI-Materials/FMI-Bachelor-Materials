#include<iostream>
#include <vector>
#include<cmath>
#include<string.h>
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
				os <<ob.coef<< "x^" << ob.grad;
		}

	}
	os << endl;
	return os;
}
istream& operator >>(istream& os, Monom& ob)
{
	cout<< "Dati un monom:(grad, coef) "<<endl;
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
	void descompun(int grad,polinom_ireductibil & r1, polinom_ireductibil & r2);



};
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


	polinom_ireductibil(const polinom_ireductibil & ob); //copy constructor

	~polinom_ireductibil() //destructor
	{}

	void print_me(ostream& os);//pur virt in polinom
	void read_me(istream& os);//pur virtuala in polinom

	polinom_ireductibil& operator =(const polinom_ireductibil& ob);
};
polinom_ireductibil::polinom_ireductibil(polinom_reductibil& ob)
{
	nr_monoame = ob.get_nrm();
	float *a;
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

polinom_ireductibil::polinom_ireductibil( const polinom_ireductibil& ob)
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
