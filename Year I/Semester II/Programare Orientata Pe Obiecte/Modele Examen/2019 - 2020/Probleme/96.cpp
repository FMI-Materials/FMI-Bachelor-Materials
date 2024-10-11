#include <iostream>
using namespace std;

class A
{
protected: int x;
public: A(int i = -16) { x = i; }
		virtual A f(A a) { return x + a.x; }
		void afisare() { cout << x; }
};
class B: public A
{
public: B(int i=3):A(i){}
		A f(A a) { return x + a.x + 1; }
};
int main()
{
	A *p1 = new B, *p2 = new A, *p3 = new A(p1->f(*p2));
	p3->afisare();
	return 0;
}
