#include <iostream>
using namespace std;
class B
{ protected: int i;
  public: B(int j=5) {cout << " cb "; i=j-2; }
          ~B(){ cout << " db ";}
          int get_i() { return i; } };

class D1: public B
{ int j;
  public: D1(int k=10) {cout << " cd1 "; j=i-k+3; }
          ~D1(){ cout << " dd1 ";} };

 class D2: public D1
{ int k;
  public: D2(int l=15) {cout << " cd2 "; k=i-l+3; }
           ~D2(){ cout << " dd2 ";}  };
D1 f(D1 d1, D2 d2) {return d1.get_i()+d2.get_i(); }
int main()
{ D2 ob2; D1 ob1(3);
  cout<<f(ob1,ob2).get_i()+ob2.get_i();
  return 0;
}
