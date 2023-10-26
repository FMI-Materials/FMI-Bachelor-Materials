#include <cstdlib>
#include <iostream>
using namespace std;
//Partea III  suprascrierea metodelor
  void f(int i,int j){cout <<" exterioara \n";}
  class B
  {public:
    void f(){cout<<" baza "; ::f(1,2);} // pentru a vedea functia exterioara ascunsa de redefinirea lui f!!!
   int  f(int i){cout<<" baza int\n "; return 1;}
   };
  class Ds: public B {public: void f(){cout<<" dSupraincarcare \n";}}; 		     // ascunde si   void f() si   int f(int)
  class Drt: public B {public: void f(int i){cout<<" dRedefinire tip intors \n"; }};	      // ascunde si   void f() si   int f(int)
  class Drp: public B {public: void f(char c,char d){cout<<" dRedefinire  parametrii \n"; }};// ascunde si   void f() si   int f(int)

int main(int argc, char *argv[])
{

// ascunderea metodelor
Ds ds;
ds.B::f(1);  // este vizibila prin specificarea clasei
//ds.f(1); //este ascunsa de supraincarcare
 ds.f(); //varianta supraincarcata din Ds

 Drt drt;
//drt.f(); //este ascunsa de redefinire -modificare tip intors
//int x=drt.f(1); //e ascunsa de redefinire
drt.B::f();
int y=drt.B::f(1);
drt.f(1); //varianta redefinita

 Drp drp;
// drp.f();// ascunsa de redefinire -tip parametrii
// drp.f(1); //ascunsa de redefinire tip parametrii
 drp.B::f();
 drp.B::f(1);
 drp.f('a','b');



             system("PAUSE");
    return 0;
}





