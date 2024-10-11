#include <iostream.h>
class B {
    int x;

public:
    B(int i = 17) { x = i; }
    int get_x() { return x; }
    operator int() { return x; }
};
class D : public B {
public:
    D(int i = -16)
        : B(i)
    {
    }
};
int main()
{
    D a;
    cout << 27 + a;
    return 0;
}