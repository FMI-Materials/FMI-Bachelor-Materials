#include <cstdlib>
#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

class B
{
public:  virtual void fv(){} // mecanism functional doar daca sunt metode virtuale
                            //pointer suplimentar si evaluare la executie
};

class D: public B
{
public:  void fv(){}
         void fsup(){cout<<"suplimentar";}
};




int main()
{B *pb;
int i;
cin>>i;
if(i) pb=new B;
      else pb=new D;
cout<<typeid(*pb).name()<<endl;// typeid(*pb).name() este codificat intern -nu neaparat "D"
if( typeid(*pb)==typeid(D)) ((D *)pb)->fsup();
else cout<<"obiect B"<<endl;

if( typeid(pb)==typeid(B*)) cout<<"poitner din B"<<endl; // chiar daca este cred obiect din D pointerul este vazut ca B*
else cout<<"pointer din D";
}

