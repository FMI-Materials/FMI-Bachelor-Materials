#include <iostream>
using namespace std;
class A
{ int x;
  static int y;
public: A(int i,int j):x(i),y(j){}
	int f() const;};
int A::y;
int A::f() const {return y;}
int main()
{ const A a(21,2);
  cout<<a.f();
return 0;
}