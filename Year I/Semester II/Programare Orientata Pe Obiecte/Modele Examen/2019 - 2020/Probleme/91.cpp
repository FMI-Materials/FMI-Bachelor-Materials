#include <iostream>
using namespace std;

class A
{
	int x;
public:
	A(int i = 25) { x = i; }
	int& f() const { return x; }
};
int main()
{
	A ob(5);
	cout << ob.f();
	return 0;
}