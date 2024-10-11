#include <iostream.h>
class B {
    int x;

public:
    B(int i = 2)
        : x(i)
    {
    }
    int get_x() const { return x; }
};
class D : public B {
    int* y;

public:
    D(int i = 2)
        : B(i)
    {
        y = new int[i];
        for (int j = 0; j < i; j++)
            y[j] = 1;
    }
    D(D& a)
    {
        y = new int[a.get_x()];
        for (int i = 0; i < a.get_x(); i++)
            y[i] = a[i];
    }
    int& operator[](int i) { return y[i]; }
};
ostream& operator<<(ostream& o, const D& a)
{
    for (int i = 0; i < a.get_x(); i++)
        o << a[i];
    return o;
}
int main()
{
    D ob(5);
    cout << ob;
    return 0;
}