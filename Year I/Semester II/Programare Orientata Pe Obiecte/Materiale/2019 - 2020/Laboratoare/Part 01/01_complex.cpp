#include <iostream>
#include <math.h>
using namespace std;

class complex {
private:
    int real;
    int imaginar;
public:
    complex (int, int);                     ///constructor initializare
    complex (complex&);                     ///constructor copiere
    ~complex ();                            ///destructor
    void set_real(int);                     ///set
    void set_imaginar(int);                 ///set
    int get_real(){return real;};           ///get
    int get_imag(){return imaginar;};       ///get
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, complex& z);  ///supraincarcare pe >>
    friend ostream& operator<<(ostream &out, complex& z); ///supraincarcare pe <<
    double modul(); ///functia modul
    complex& operator=(complex &z); ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)
    friend complex& operator+(complex& z1, complex& z2); ///supraincarcare operator +
    friend complex& operator*(complex& z1, complex& z2); ///supraincarcare operator *
    friend complex& operator/(complex& z1, complex& z2); ///supraincarcare operator /
};
complex::complex(int real = 0, int imaginar = 0){
    this->real = real;
    this->imaginar = imaginar;
}
complex::complex(complex &z){
    this->real = z.real;
    this->imaginar = z.imaginar;
}
complex::~complex(){
    this->real=0;
    this->imaginar=0;
}
void complex::set_real(int x){
    real = x;
}
void complex::set_imaginar(int y){
    imaginar=y;
}
void complex::citire(istream &in){
    cout<<"Cititi partea reala: ";
    in>>real;
    cout<<"Cititi partea imaginara: ";
    in>>imaginar;
}
istream& operator>>(istream& in,complex& z){
    z.citire(in);
    return in;
}
void complex::afisare(ostream &out){
    if (imaginar==0) {
        out<<real;
    }
    else{
        if (imaginar < 0){
            out<<real<<imaginar<<"*i";
        }
        else{
            out<<real<<"+"<<imaginar<<"*i";
        }
    }
}
ostream& operator<<(ostream& out, complex& z){
    z.afisare(out);
    return out;
}
double complex::modul(){
    return sqrt(real*real+imaginar*imaginar);
}
complex& complex::operator=(complex &z){
    real=z.real;
    imaginar=z.imaginar;
}
inline complex& operator+(complex &z1, complex& z2){
    complex *z = new complex;
    z->real = z1.real + z2.real;
    z->imaginar = z1.imaginar + z2.imaginar;
    return *z;
}
inline complex& operator*(complex &z1, complex& z2){
    complex *z=new complex;
    z->real = z1.real * z2.real - z1.imaginar * z2.imaginar;
    z->imaginar = z1.real * z2.imaginar + z2.real * z1.imaginar;
    return *z;
}
complex& operator/(complex &z1, complex &z2){
    complex *z=new complex;
    z->real = (z1.real*z2.real + z1.imaginar * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    z->imaginar = (z2.real * z1.imaginar - z1.real * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    return *z;
}
int main()
{
    complex z1;
    cin>>z1;
    complex z2(z1);
    complex z=z1+z2;
    cout<<z<<endl;
    return 0;
}
