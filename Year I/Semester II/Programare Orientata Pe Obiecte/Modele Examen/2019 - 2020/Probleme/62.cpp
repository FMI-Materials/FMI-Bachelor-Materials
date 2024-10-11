#include <iostream.h>

class cls {
    int vi;

public:
    cls(int v = 18) { vi = v; }
    operator int() { return vi; }
    cls operator++()
    {
        vi++;
        return *this;
    }
    cls operator++(int);
};

cls cls::operator++(int)
{
    cls aux = *this;
    vi++;
    return aux;
}

void main()
{
    cls p(20);
    int x = p++, y = ++p;
    cout << "x=" << x << ", y=" << y << endl;
}
