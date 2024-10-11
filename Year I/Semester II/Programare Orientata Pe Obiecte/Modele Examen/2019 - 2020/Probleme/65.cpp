#include <iostream.h>

class vector {
    int *p, nr;

public:
    operator int() { return nr; }
    vector(int);
};

vector::vector(int n)
{
    p = new int[n];
    nr = n;
    while (n--)
        p[n] = n;
}

void f(int i)
{
    while (i--)
        cout << i << endl;
}

void main()
{
    vector x(10);
    f(x);
}
