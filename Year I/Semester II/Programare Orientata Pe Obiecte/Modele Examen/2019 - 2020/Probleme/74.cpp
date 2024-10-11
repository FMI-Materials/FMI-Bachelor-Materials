#include <iostream.h>
class cls {
    int vi;

public:
    cls(int v = 37) { vi = v; }
    friend int& f(cls);
};
int& f(cls c) { return c.vi; }
int main()
{
    const cls d(15);
    f(d) = 8;
    cout << f(d);
    return 0;
}