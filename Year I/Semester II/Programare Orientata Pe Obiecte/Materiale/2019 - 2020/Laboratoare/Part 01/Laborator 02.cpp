#include <iostream>
#include <string.h>
using namespace std;
class persoana{
private:
    char *nume;

public:
    persoana(char *num = NULL, int x=0)
    {
        if (num != NULL)
        {this->nume=new char[strlen(num)];
        strcpy(nume,num);}
        else
            this->nume=num;
    }
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, persoana& z);
    friend ostream& operator<<(ostream &out, persoana& z);
};
void persoana::citire(istream &in){
    cout<<"Cititi numele: ";
    char num[256];
    in.getline(num,256);
    nume=new char [strlen(num)];
    strcpy(nume,num);
}
istream& operator>>(istream& in,persoana& z){
    z.citire(in);
    return in;
}
void persoana::afisare(ostream &out){
    out<<nume;
}
ostream& operator<<(ostream& out, persoana& z){
    z.afisare(out);
    return out;
}
int main()
{
    persoana p;
    cin>>p;
    cout<<p;
    return 0;
}
