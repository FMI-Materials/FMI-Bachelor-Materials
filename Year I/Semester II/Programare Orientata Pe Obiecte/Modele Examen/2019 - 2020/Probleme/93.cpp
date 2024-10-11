#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
	int i;
public: A() { i = 1; }
		int get_i() { return i; }
};
class B: public A
{
	int j;
public: B() { j = 2; }
		int get_j() { return j; }
};
int main()
{
	A *p;
	int x = 0;
	if (x) p = new A;
	else p = new B;
	if (typeid(p).name() == typeid(B*).name()) cout << ((B*)p)->get_j();
	else cout << "tipuri diferite";
	return 0;
}

