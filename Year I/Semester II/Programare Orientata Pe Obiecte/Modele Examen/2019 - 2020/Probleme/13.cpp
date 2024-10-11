#include <iostream>
using namespace std;
int f(int y)
{
    try {
        if (y > 0)
            throw y;
    }
    catch (int i) {
        throw;
    }
    return y - 2;
}
int f(int y, int z)
{
    try {
        if (y < z)
            throw z - y;
    }
    catch (int i) {
        throw;
    }
    return y + 2;
}
float f(float& y)
{
    cout << " y este referinta";
    return (float)y / 2;
}
int main()
{
    int x;
    try {
        cout << "Da-mi un numar par: ";
        cin >> x;
        if (x % 2)
            x = f(x, 0);
        else
            x = f(x);
        cout << "Numarul " << x << " e bun!" << endl;
    }
    catch (int i) {
        cout << "Numarul " << i << " nu e bun!" << endl;
    }
    return 0;
}