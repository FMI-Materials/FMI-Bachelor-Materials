#include <iostream>
using namespace std;
class A {
    int x;

public:
    A(int i) { x = i; }
    int get_x() { return x; }
    int& set_x(int i) { x = i; }
    A operator=(A a1)
    {
        set_x(a1.get_x());
        return a1;
    }
};
class B : public A {
    int y;

public:
    B(int i)
        : A(i)
    {
        y = i;
    }
    void afisare() { cout << y; }
};
int main()
{
    B a(112), b, *c;
    cout << (b = a).get_x();
    (c = &a)->afisare();
    return 0;
}