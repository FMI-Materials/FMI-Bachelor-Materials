#include <iostream>
#include <string>

using namespace std;

class polinom
{
    private:
        int n; // gradul polinomului
        double c[100]; //vectorul de coeficienti
    public:
        polinom(); // constructor de initializare fara parametri
        polinom(int n, double c[100]); // constructor de initializare cu parametri
        polinom(const polinom &p); // constructor de copiere
        ~polinom(); // destructor

        void set_polinom(double v[100], int n); // setter polinom
        double get_element(int i); // getter element de pe pozitia i
        int get_grad(); // getter grad polinom
        void afisare_vector(); // getter vector de coeficienti
        double punct(int x); // calculeaza valoarea polinomului in punctul x

        // supraincarcarea operatorilor I/O
        friend istream& operator>>(istream& in,polinom& p);
        friend ostream& operator<<(ostream& out,const polinom& p);

        // supraincarcarea operatorilor aritmetici
        polinom operator+ (const polinom& p);
        polinom operator- (const polinom& p);
        polinom operator* (const polinom& p);
};

polinom::polinom() // constructor fara parametri
{
        n = 0;
        c[100] = {0};
}

polinom::polinom(int n, double c[100]) // constructor cu parametri
{
        this->n = n;
        for (int i=0; i<= n; i++)
            this->c[i] = c[i];
}

polinom::polinom (const polinom &p) // constructorul de copiere
{
    this->n = p.n;
    for (int i=0; i<=n; i++)
        this->c[i] = p.c[i];
}

polinom::~polinom() // destructor
{
    n = 0;
}

void polinom::set_polinom(double c[100], int n) // setter grad si vector de coeficienti
{
    int i;
    this->n = n;
    for (i = 0; i <= n; i++)
        this->c[i] = c[i];
}

double polinom::get_element(int i) // getter element de pe pozitia i
{
    return c[i];
}

int polinom::get_grad() // getter grad polinom
{
    return n;
}

void polinom::afisare_vector() // getter vector de coeficienti
{
    for (int i = 0; i <= n; i++)
        cout<< c[i]<< " ";
}

double polinom::punct(int x) // calculeaza valoarea polinomului in punctul x
{
    int val = 0, x_curent,i;
    x_curent = 1;
    for (i = 0; i <= n; i++)
    {
        val = val + c[i] * x_curent;
        x_curent = x_curent*x;
    }
    return val;
}

// supraincarcarea operatorilor I/O

istream& operator>>(istream& in,polinom& p)
{
    cout<<"Grad polinom: ";
    in>>p.n;
    cout<<"Coeficienti polinom: ";
    for (int i = 0; i <= p.n; i ++)
        in>>p.c[i];

    return in;
}

ostream& operator<<(ostream& out,const polinom& p)
{
    out<<"Grad polinom: "<<p.n;
    out<<"\nCoeficienti polinom: ";
    for (int i = 0; i <= p.n; i ++)
        out<<p.c[i]<<" ";
    out<<"\n";

    return out;
}

// supraincarcarea operatorilor aritmetici

polinom polinom::operator+(const polinom& p)
{
    polinom aux;
    aux.n = 0;
    int i;
    for (i = 0; i <= max(this->n, p.n); i++)
    {
        aux.c[i] = this->c[i] + p.c[i];
        if (aux.c[i] != 0) aux.n = i;
    }
    return aux;
}

polinom polinom::operator-(const polinom& p)
{
    polinom aux;
    aux.n = 0;
    int i;
    for (i = 0; i <= max(this->n, p.n); i++)
    {
        aux.c[i] = this->c[i] - p.c[i];
        if (aux.c[i] != 0) aux.n = i;
    }
    return aux;
}

polinom polinom::operator*(const polinom& p)
{
    polinom aux;
    int nr = 0;
    aux.n = this->n + p.n;
    for (int i = 0; i <= this->n; i++)
        for (int j = 0; j <= p.n; j++)
        {
            aux.c[i+j] = aux.c[i+j] + this->c[i]*p.c[j];
        }
    return aux;
}

// main entry

int main()
{
    polinom p[100];
    int n, m, i, index = 0;
    int k = 1;

    cout<< "Programul lucreaza cu n polinoame numerotate de la 1 la n\n";

    while (k == 1)
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza 1 pentru a citi n polinoame\n";
        cout<<"Tasteaza 2 pentru a afisa primele n polinoame\n";
        cout<<"Tasteaza 3 pentru a afisa polinomul n\n";
        cout<<"Tasteaza 4 pentru a afisa coeficientul de grad i din polinomul n\n";
        cout<<"Tasteaza 5 pentru a afisa toti coeficientii polinomului n\n";
        cout<<"Tasteaza 6 pentru a calcula valoarea in punctul x in polinom n\n";
        cout<<"Tasteaza 7 pentru a calcula suma polinoamelor n si m\n";
        cout<<"Tasteaza 8 pentru a calcula diferenta polinoamelor n si m\n";
        cout<<"Tasteaza 9 pentru a calcula produsul polinoamelor n si m\n";
        cout<<"Tasteaza 0 pentru a iesi din program\n";
        cout<<"-------------------------------------------------------\n";

        int comanda;
        cin>>comanda;
        switch(comanda)
        {
            case 1:
            {
                cout<<"n = ";
                cin>>n;
                for (i = 0; i < n; i++)
                    cin>> p[index++];
                cout<<endl;
                break;
            }
            case 2:
            {
                cout<< "n = ";
                cin>> n;
                for (i = 0; i < n; i++)
                    cout<<p[i];
                cout<<endl;
                break;
            }
            case 3:
            {
                cout<< "n = ";
                cin>> n;
                cout<< p[n-1];
                cout<<endl;
                break;
            }
            case 4:
            {
                cout<< "n = ";
                cin>> n;
                cout<< "i = ";
                cin>> i;
                cout<<p[n-1].get_element(i);
                cout<<endl;
                break;
            }
            case 5:
            {
                cout<< "n = ";
                cin>> n;
                p[n-1].afisare_vector();
                cout<<endl;
                break;
            }
            case 6:
            {
                int x;
                cout<< "n = ";
                cin>> n;
                cout<<"x = ";
                cin>>x;
                cout<<p[n-1].punct(x)<<endl;
                break;
            }
            case 7:
            {
                cout<< "n = ";
                cin>> n;
                cout<< "m = ";
                cin>> m;
                cout<< p[n-1] + p[m-1];
                cout<<endl;
                break;
            }
            case 8:
            {
                cout<< "n = ";
                cin>> n;
                cout<< "m = ";
                cin>> m;
                cout<< p[n-1] - p[m-1];
                cout<<endl;
                break;
            }
            case 9:
            {
                cout<< "n = ";
                cin>> n;
                cout<< "m = ";
                cin>> m;
                cout<< p[n-1] * p[m-1];
                cout<<endl;
                k = 1;
                break;
            }
            case 0:
            {
                cout<< "Program incheiat\n";
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }

    return 0;
}
