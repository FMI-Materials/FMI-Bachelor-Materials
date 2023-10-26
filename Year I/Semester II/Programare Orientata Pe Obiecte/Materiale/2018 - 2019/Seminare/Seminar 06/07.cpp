#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class B
{
public: virtual void fv(){}
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
D *pd; 
if(pd= dynamic_cast<D*>(pb)){pd->fsup();} // daca nu se face conversia intoarce NULL

}

