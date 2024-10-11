#include <iostream.h>
class B {
    int i;

public:
    B() { i = 1; }
    virtual int get_i() { return i; }
};
class D : virtual public B {
    int j;

public:
    D() { j = 2; }
    int get_i() { return B::get_i() + j; }
};
class D2 : virtual public B {
    int j2;

public:
    D2() { j2 = 3; }
    int get_i() { return B::get_i() + j2; }
};
class MM : public D, public D2 {
    int x;

public:
    MM() { x = D::get_i() + D2::get_i(); }
    int get_i() { return x; }
};
int main()
{
    B* o = new MM();
    cout << o->get_i() << "\n";
    MM* p = dynamic_cast<MM*>(o);
    if (p)
        cout << p->get_i() << "\n";
    D* p2 = dynamic_cast<D*>(o);
    if (p2)
        cout << p2->get_i() << "\n";
    return 0;
}
