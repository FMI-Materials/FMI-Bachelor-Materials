#include <iostream.h>

class D;

class B {
    int x;
    friend void f(B, D);

public:
    B(int i = 0) { x = i; }
};

class D : public B {
public:
    int y;
    D(int i = 0, int j = 0)
        : B(i)
    {
        y = j;
    }
};

void f(B b, D d) { cout << b.x << " " << d.y; }

void main()
{
    B b;
    D d;
    f(b, d);
}
