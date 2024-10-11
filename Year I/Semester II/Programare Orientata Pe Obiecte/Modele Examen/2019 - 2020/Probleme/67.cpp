#include <iostream.h>

class Y;

class Z;

class X {
    int x;

public:
    X(int n = 0) { x = n; }
    friend Y;
};

class Y {
    int y;
    friend Z;
};

class Z {
public:
    void f(X u) { cout << u.x; }
};

void main()
{
    X a;
    Z b;
    b.f(a);
}
