#include <iostream.h>

class cls2;

class cls1 {
public:
    int vi;
    cls1(int v = 30) { vi = v; }
    cls1(cls2 p) { vi = p.vi; }
};

class cls2 {
public:
    int vi;
    cls2(int v = 20) { vi = v; }
};

cls1 f(cls1 p)
{
    p.vi++;
    return p;
}

void main()
{
    cls1 p;
    f(p);
    cout << endl
         << p.vi;
    cls2 r;
    f(r);
    cout << endl
         << r.vi;
}
