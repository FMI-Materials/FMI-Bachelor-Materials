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
		A f(A a) { return x + 1; }
		B operator+ (B a) { return x + a.x; }
};
int main()
{
	B a; int b = -21;
	a += b;
	cout << b;
	return 0;

}