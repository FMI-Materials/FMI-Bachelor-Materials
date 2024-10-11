#include <iostream.h>
int f(int y)
{
    if (y < 0)
        throw y;
    return y / 2;
}
int f(int y, int z)
{
    if (y < z)
        throw z - y;
    return y / 2;
}
float f(int& y)
{
    cout <<” y este referinta”;
    return (float)y / 2;
}
int main()
{
    int x;
    try {
        cout <<”Da - mi un numar par : ”;
        cin >> x;
        if (x % 2)
            x = f(x, 0);
        else
            x = f(x); //(1)
        cout <<”Numarul ”<< x <<” e bun !”<< endl;
    }
    catch (int i) {
        cout <<”Numarul ”<< i <<” nu e bun !”<< endl;
    }
    return 0;
}
