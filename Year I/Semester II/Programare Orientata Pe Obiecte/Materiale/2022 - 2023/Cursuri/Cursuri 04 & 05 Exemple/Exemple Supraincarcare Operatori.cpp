#include <iostream>

using namespace std;

/*****     operatorii se mostenesc (majoritatea) **********/

/******************* supraincarcarea op de citire - var 2 - fara functia membra de citire ************/
/*
class Test
{
protected:
    int x,y;
public:
    friend istream& operator>>(istream&, Test&);
};

class Deriv: public Test{
public:
    friend istream& operator>>(istream&, Deriv&);
};

istream& operator>>(istream& in, Test& ob)
{
    cout<<"In TEST ca si clasa de baza: ";
        in>>ob.x>>ob.y;
    return in;
}


istream& operator>>(istream& in, Deriv& ob)
{
    cout<<"In TEST ca si clasa DERIVATA: ";
        in>>ob.x>>ob.y;
    return in;
}

int main()
{
    Test A;
    cin>>A;
    /// operator>>(cin, A);
    Deriv B;
    cin>>B;  /// trebuie rescris operatorul de citire, altfel il ia pe cel de la tata
}
*/

/******************* supraincarcarea op de citire  - var 2 - cu functia membra de citire virtuala ************/
/*
class Test
{
protected:
        int x,y;
public:
    virtual void citire(istream& in)
    {
        cout<<"In TEST: ";
        in>>x>>y;
    }
    friend istream& operator>>(istream&, Test&);
};

class Deriv: public Test{
public:
        void citire(istream& in)
    {
        cout<<"In TEST in derivata: ";
        in>>x>>y;
    }
};

istream& operator>>(istream& in, Test& ob) ///daca functia de citire devine virtuala si e rescrisa in deriv, nu mai e nevoie sa rescriem si operatorul
{
    ob.citire(in);
    return in;
}

int main()
{
    Test A;
    cin>>A;
    /// operator>>(cin, A);
    Deriv B;
    cin>>B;
}
*/
/***************************************/

/*****************  alt exemplu supraincarcare operatori  *********************************************/
/*
class student
{
  string nume;
  int grupa;
  public:
  void set_nume(string s) { nume = s;}
  void set_grupa(int x) {grupa = x;}
  string get_nume(){return nume;}
  int get_grupa(){return grupa;}
  student(string s = "Anonim", int g = 0){nume = s; grupa = g;}
  friend istream& operator>> (istream& in, student& s);
  friend ostream& operator<<(ostream& out, student& s);
  // student operator+(string);  /// supraincarcarea op +  ca functie membra
  friend student operator+(student, string);
  friend student operator+(string, student);
  student operator+(int);
  student operator+=(int);
  student operator=(student);
  void afisare();
  student(const student&);
  ~student();
};

student::~student()
{
    cout<<"\n Destructor   "<<nume<<endl;
}

student::student(const student& ob)
{
    cout<<"\n Constructor de copiere explicit\n";
    nume = ob.nume;
    this->grupa = ob.grupa;
}

void student::afisare()
{
    cout<<nume<<"  "<<grupa<<endl;
}

student operator+(student A, string s)
{
    student temp (A);  /// copie obiectului actual = obiectul care apeleaza functia
    temp.nume = temp.nume + s;
    return temp;
}

student operator+(string s, student A)
{
    student temp (A);  /// copie obiectului actual = obiectul care apeleaza functia
    temp.nume = temp.nume + s;
    return temp;
}

student student::operator+(int x)
{
    student temp (*this);  /// copie obiectului actual = obiectul care apeleaza functia
    temp.grupa = temp.grupa + x;
    return temp;
}

student student::operator+=(int x)
{
    grupa += x;
    return *this;
}

student student::operator=(student ob)
{
    if (this != &ob)
    {
        cout<<"\n operator de atribuire explicit \n";
        this->nume = ob.nume;
        this->grupa = ob.grupa;
    }
    return *this;
}


student student::operator+(string s)
{
    student temp (*this);  /// copie obiectului actual = obiectul care apeleaza functia
    temp.nume = temp.nume + s;
    return temp;
}


istream& operator>> (istream& in, student& s)
{
    cout<<"Nume:  ";
    in >> s.nume;
    cout<<"Grupa:  ";
    in>>s.grupa;
    return in;
}

ostream& operator<<(ostream& out, student& s)
{
    out<<s.nume<<"  "<<s.grupa<<endl;
    return out;
}

int main()
{
    student A;
    /// set si get
    A.set_nume("Ionescu");
    A.set_grupa(132);
    cout<<A.get_nume()<<"  "<<A.get_grupa()<<endl;

    student B, C("Popescu"), D("Ana",132), E(D);  /// constructorii

/// supraincarcare operatori
    cin>>B;   /// operator>>(cin,B)
    //cout<<B<<C;  /// operator<< (operator<<(cout,B), C)

D = D + " Maria";
cout<<D;
   /// D = D + " Maria";  /// Ana Maria, 132 ===> student operator+(string)
    /// D + "Maria";   D.operator+("Maria")  ===> void operator+(string) --- functie membra sau
    ///student operator+(student,string) -- functie prieten
    /// D = D + "Maria";  D.operator=(D.operator+(string))

    D = "Mirabela " + D;
    cout<<D;

    E = E + 1;  /// Ana Maria ajunge la 133 /// E.operator=(E.operator+(int))
    cout<<E;

    B += 100; /// B e in anul 2, grupa 232
    cout<<B;


    student F;
    F = B;   /// operator de atribuire;  F.operator=(B)
    cout<<F;

    int n;
    student v[30];

    cout<<"Dati grupa: - nr studenti: "; cin>>n;

    for(int i = 0; i <n ; i++)
   /// v[i].citire(); /// cin>>v[i];

     for(int i = 0; i<n; i++)
     v[i].afisare();  /// mergea direct cout<<v[i]; pt ca e supraincarcat cout; de dragul didacticii...

    return 0;
}
*/

/*************  exemplu operator== ca fct membra si ca fct prieten: nr de operanzi difera ******************/
/*
class Test
{
    int x;
    public:
        Test(int i){x = i;}
        friend int operator==(Test M, Test N)
        {
            if (M.x == N.x) return 1;
            return 0;
        }

        int operator==(Test N)
        {
            if (this->x == N.x) return 1;
            return 0;
        }
};

int main()
{
    Test A(2), B(3);
    if (A == B) cout<<"egale";    /// A == B; A.operator==(B)
    else cout<<"nu sunt egale";
}
*/

/**********************  exemplu mai multi operatori supraincarcati  **********************************/
/*
#include <iostream>

using namespace std;

class Test
{
    int a,b;
    public:
    friend istream& operator>>(istream&, Test&);
   // istream& operator>>(istream&);
    friend ostream& operator<<(ostream&, Test&);
    friend Test operator+(const Test&, const Test&);
    Test operator+(const Test&);
   // friend int operator<(Test,Test);
    int operator<(Test);
    int operator==(Test);
    Test operator++();
    Test operator++(int);
};

int main()
{
    Test x,y;

///    x >> cin; ///x.operator>>(cin)
    cin>>x>>y; /// operator>>(cin,x)
    cout<<x<<" "<<y<<endl;

    Test z;
    z = x + y;
    cout<<z<<endl;
    if (x < y) cout <<z<<endl;
    else if (x == y) cout<<"egalitate\n";
    else
    {
        ++z;
        z++;
        cout<<z<<endl;
    }
return 0;
}

Test Test::operator++()
{
    a++;
    b++;
    return *this;
}

Test Test::operator++(int)
{
    a++;
    b++;
    return *this;
}

int Test::operator< (Test ob2)
{
    return (a < ob2.a) && (b < ob2.b);
}

int Test::operator== (Test ob2)
{
    return (a == ob2.a) && (b == ob2.b);
}

/*int operator< (Test ob1, Test ob2)
{
    return (ob1.a < ob2.a) && (ob1.b < ob2.b);
}
*/
/*
Test operator+(const Test& ob1, const Test& ob)
{
    cout<<"F"<<endl;
    Test rez;
    rez.a = ob1.a + ob.a;
    rez.b = ob1.b + ob.b;
    return rez;
}

Test Test::operator+(const Test& ob)
{
    cout<<"M"<<endl;
    Test rez;
    rez.a = this->a + ob.a;
    rez.b = this->b + ob.b;  /// rez.b = b + ob.b;
    return rez;
}

/// istream& Test::operator>>(istream& in)
/// {
///     in>>a>>b; /// this->a    this->b
///     return in;
/// }

istream& operator>>(istream& in, Test& ob)
{
    in>>ob.a>>ob.b;
    return in;
}

ostream& operator<<(ostream& out, Test& ob)
{
    out<<ob.a<<" "<<ob.b<<endl;
    return out;
}


