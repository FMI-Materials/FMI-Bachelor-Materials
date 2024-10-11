#include <iostream.h>
template <class tip>
tip dif(tip x, tip y)
{
    return x - y;
}
unsigned dif(unsigned x, unsigned y)
{
    return x >= y ? x - y : y - x;
}
int main()
{
    unsigned i = 7, j = 8;
    cout << dif(i, j);
    return 0;
}