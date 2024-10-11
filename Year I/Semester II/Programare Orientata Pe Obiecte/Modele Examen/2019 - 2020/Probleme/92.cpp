


#include <iostream>
using namespace std;

class A
{
	int x;
public:
	A(int i):x(i){}
	int get_x() const { return x; }
};
class B : public A
{
	int *y;
public:
	B(int i) :A(i)
	{
		y = new int[i];
		for (int j = 0; j < i; j++) y[j] = 1;
	}
	B(B&);
	int &operator[](int i) { return y[i]; }
};
B::B(B& a)
{
	y = new int[a.get_x()]; 
	for (int i = 0; i < a.get_x(); i++) y[i] = a[i];
}
ostream &operator<<(ostream& o, B a)
{
	for (int i = 0; i < a.get_x(); i++)o << a[i];
	return o;
}
int main()
{
	B b(5);
	cout << b;
	return 0;
}