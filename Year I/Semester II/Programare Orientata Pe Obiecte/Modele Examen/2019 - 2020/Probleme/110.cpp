#include <iostream>
using namespace std;
class A
{ protected: static int x;
  public: A(int i=1) {x=i; }
  int get_x() { return x; }
  int& set_x(int i) { int y=x; x=i; return y;}
  A operator=(A a1) { set_x(a1.get_x()); return a1;}
} a(33);
int main()
{ A a(18), b(7);
  cout<<(b=a).set_x(27);
  return 0;
}
