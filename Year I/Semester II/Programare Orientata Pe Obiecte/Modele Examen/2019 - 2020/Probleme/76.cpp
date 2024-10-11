#include <iostream.h>
class cls {
    int x;

public:
    cls(int i = 25) { x = i; }
    int f();
};
int cls::f() { return x; }
int main()
{
    const cls d(15);
    cout << d.f();
    return 0;
}