#include <iostream>
using namespace std;
class B {
protected:
    int x;

public:
    B(int i = 12) { x = i; }
    virtual B f(B ob) { return x + ob.x + 1; }
    void afisare() { cout << x; }
};
class D : public B {
public:
    D(int i = -15)
        : B(i - 1)
    {
        x++;
    }
    B f(B ob) { return x - 2; }
};
int main()
{
    B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));
    p3->afisare();
    return 0;
}