#include <iostream.h>
class cls {
    int *v, nr;

public:
    cls(int i = 0)
    {
        nr = i;
        v = new int[i];
        for (int j = 0; j < size(); j++)
            v[j] = 3 * j;
    }
    ~cls() { delete[] v; }
    int size() { return nr; }
    int& operator[](int i) { return v[i]; }
    cls operator+(cls);
};
cls cls::operator+(cls y)
{
    cls x(size());
    for (int i = 0; i < size(); i++)
        x[i] = v[i] + y[i];
    return x;
}
int main()
{
    cls x(10), y = x, z;
    x[3] = y[6] = -15;
    z = x + y;
    for (int i = 0; i < x.size(); i++)
        cout << z[i];
    return 0;
}
