#include <iostream.h>
class cls {
    int *v, nr;

public:
    cls(int i)
    {
        nr = i;
        v = new int[i];
        for (int j = 1; j < nr; j++)
            v[j] = 0;
    }
    int size() { return nr; }
    int& operator[](int i) { return *(v + i); }
};
int main()
{
    cls x(10);
    x[4] = -15;
    for (int i = 0; i < x.size(); i++)
        cout << x[i];
    return 0;
}