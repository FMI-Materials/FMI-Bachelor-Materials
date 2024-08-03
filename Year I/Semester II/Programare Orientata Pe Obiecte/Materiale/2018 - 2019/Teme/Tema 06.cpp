#include<iostream>
using namespace std;
class multime
{
    int* v, dim;
public:
    multime()//constructor de initializare ca sa pot face declaratia multime C;
    {
        dim = 0;
        v = new int[dim];
    }
    multime(int n, int a[]);//constructor initializare
    multime(const multime& m);//constructor de copiere

    ~multime()//destructor
    {
        dim = 0;
        delete[]v;
    }

    multime operator + (const multime& m);
    multime operator * (const multime& m);
    multime operator - (const multime& m);

    void transf(int& n, int a[]); //metoda publica pentru transformarea unui vector in multime
    friend ostream& operator <<(ostream& os, multime& ob);//pentru afisare
    friend istream& operator >> (istream& os, multime& ob);//pentru citire

    multime& operator =(const multime& ob);

};
istream& operator >> (istream& os, multime& ob)
{
    int i;
    cout <<"dati nr elemente: ";
    os >> ob.dim;
    ob.v = new int[ob.dim];
    cout << "dati elementele: " << endl;
    for (i = 0; i < ob.dim; i++)
        os >> ob.v[i];
    return os;
}
ostream& operator <<(ostream& os, multime& ob)
{
    int i;
    for (i = 0; i < ob.dim; i++)
        os << ob.v[i] << " ";
    os << endl;
    return os;
}
multime& multime :: operator =(const multime& ob)
{
    dim = ob.dim;
    int i;
    for (i = 0; i < dim; i++)
        v[i] = ob.v[i];
    return *this;
}
multime multime :: operator -(const multime& m)
{
    multime nou;
    int len, j, i, k = 0;
    if (m.dim < dim)
        len = m.dim;
    else
        len = dim;
    nou.v = new int[len];
    for (i = 0; i < dim; i++)
    {
        int bec = 0;
        for (j = 0; j < m.dim; j++)
            if (m.v[j] == v[i])
            {
                bec = 1;
                break;
            }
        if (bec == 0)
            nou.v[k++] = v[i];

    }
    nou.dim = k;
    return nou;

}
multime multime :: operator *(const multime& m)
{
    multime nou;
    int len, j, i, k = 0;
    if (m.dim < dim)
        len = m.dim;
    else
        len = dim;
    nou.v = new int[len];
    for (i = 0; i < dim; i++)
    {
        int bec = 0;
        for (j = 0; j < m.dim; j++)
            if (m.v[j] == v[i])
            {
                bec = 1;
                break;
            }
        if (bec == 1)
            nou.v[k++] = v[i];

    }
    nou.dim = k;
    return nou;
}
multime multime:: operator + (const multime& m)
{
    multime nou;
    int i, k = 0;
    int* c;
    c = new int[dim + m.dim];
    for (i = 0; i < dim; i++)
        c[k++] = v[i];
    for (i = 0; i < m.dim; i++)
        c[k++] = m.v[i];

    transf(k, c);
    nou.v = new int[k];
    for (i = 0; i < k; i++)
        nou.v[i] = c[i];


    nou.dim = k;

    return nou;

}

multime::multime(int n, int a[])
{
    transf(n, a);
    dim = n;
    int i;
    for (i = 0; i < dim; i++)
        v[i] = a[i];

}

multime::multime(const multime& m)
{
    dim = m.dim;
    int i;
    for (i = 0; i < dim; i++)
        v[i] = m.v[i];
}

void multime::transf(int& n, int a[])
{

    int* t;
    t = new int[n];
    int i, j, bec, k = 0;
    for (i = 0; i < n; i++)
    {
        bec = 0;
        for (j = 0; j < k; j++)
            if (a[i] == t[j])
                bec = 1;
        if (bec == 0)
            t[k++] = a[i];

    }

    for (i = 0; i < k; i++)
        a[i] = t[i];
    n = k;
    delete[]t;

}

void citesc()
{
    int n, i;
    cout << "n clase=";
    cin >> n;
    multime* v;
    v = new multime[n];
    for (i = 0; i < n; i++)//citire n clase
    {
        int j, len, * a;
        cout << "lungime vector= ";
        cin >> len;
        a = new int[len];
        cout << "componente vector: " << endl;
        for (j = 0; j < len; j++)
            cin >> a[j];
        multime C(len, a);
        delete[]a;
        v[i] = C;
    }
    cout << "afisare clase introduse" << endl;
    for (i = 0; i < n; i++)
    {
        cout << v[i];
    }
}

int main()
{
   citesc();//functie pentru citirea a n obiecte

    int a[] = { 1,2,2,4,5 }, b[] = { 9,9,10,10,7,7,2 };
    multime A(5, a);
    multime B(7, b);
    multime C;

    cout << "afisare clase:" << endl;

    cout << "clasa A: ";
    cout << A;
    cout << "clasa B: ";
    cout << B;
    C = A + B;//reuniune
    cout << "reuniune A cu B" << endl;
    cout << C;
    C = A - B;//diferenta
    cout << "diferenta A-B" << endl;
    cout << C;
    C = B - A;
    cout << "diferenta B-A" << endl;
    cout << C;
    cout << "intersectia A cu B" << endl;
    C = A * B;//intersectie
    cout << C;
    return 0;

}

