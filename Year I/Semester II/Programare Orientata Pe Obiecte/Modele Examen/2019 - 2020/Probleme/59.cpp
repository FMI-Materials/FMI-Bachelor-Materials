#include <iostream.h>

class B {
    int x;

public:
    B(int v) { v = x; }
    int get_x() { return x; }
};

class D : private B {
    int y;

public:
    D(int v)
        : B(v)
    {
    }
    int get_x() { return x; }
};

void main()
{
    D d(10);
    cout << d.get_x();
}
