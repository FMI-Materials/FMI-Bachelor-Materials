#include <iostream.h>
class cls {
    static int x;

public:
    cls(int i = 1) { x = i; }
    cls f(cls a) { return x + a.x; }
    static int g() { return f() / 2; }
};
int cls::x = 7;
int main()
{
    cls ob;
    cout << cls::g();
    return 0;
}