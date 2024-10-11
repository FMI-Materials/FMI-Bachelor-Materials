#include <iostream.h>
class B {
    int x;

public:
    B(int i = 7) { x = i; }
    int get_x() { return x; }
    operator int() { return x; }
};
class D : public B {
public:
    D(int i = -12)
        : B(i)
    {
    }
    D operator+(D a) { return get_x() + a.get_x() + 1; }
};
int main()
{
    D a;
    int b = 18;
    b += a;
    cout << b;
    return 0;
}
