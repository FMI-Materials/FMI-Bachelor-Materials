#include <iostream>
using namespace std;

class A
{
	int x;
public: A(int i = 17) { x = i; }
		int get_x() { return x; }
};
class B
{
	int x;
public: B(int i = -16) { x = i; }
		operator A() { return x; }
		int get_x() { return x; }
};
int main()
{
	B a;
	A b = a;
	cout << b.get_x();
	return 0;
}

