#include <cstdlib>
#include <iostream>
using namespace std;
class prisma
{double h;
public: prisma(int ph){h=ph;}
virtual double arie()=0;
double volum(){return h*arie();}
};

class cilindru: public prisma
{double r;
public: cilindru(double ph,double pr):prisma(ph){r=pr;}
       double arie(){return 3.14*r*r;}
};

class prismaPatr: public prisma
{double l;
public: prismaPatr(double ph,double pl):prisma(ph){l=pl;}
       double arie(){return l*l;}
};

 
int main(int argc, char *argv[])
{ prisma * vp[10];
   vp[0]=new cilindru(5,5);
   vp[1]=new prismaPatr(5,5);
   
   for (int i=0;i<2;i++) cout<<vp[i]->arie()<<vp[i]->volum();
	
    system("PAUSE");
    return 0;
}



