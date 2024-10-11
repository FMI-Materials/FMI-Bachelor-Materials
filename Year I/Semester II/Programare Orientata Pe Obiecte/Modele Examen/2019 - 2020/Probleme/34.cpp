#include <iostream.h>
template <class T, class U>
T f(T x, U y)
{
    return x + y;
}
int f(int x, int y)
{
    return x - y;
}
int main()
{
    int *a = new int(3), b(23);
    cout << *f(a, b);
    return 0;
}
