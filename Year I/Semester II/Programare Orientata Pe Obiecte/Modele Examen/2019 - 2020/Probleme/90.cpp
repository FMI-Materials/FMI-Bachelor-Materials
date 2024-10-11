#include <iostream.h>
template <class T>
int f(T x, T y)
{
    return x + y;
}
int f(int x, int y)
{
    return x - y;
}
int main()
{
    int a = 5;
    float b = 8.6;
    cout << f(a, b);
    return 0;
}