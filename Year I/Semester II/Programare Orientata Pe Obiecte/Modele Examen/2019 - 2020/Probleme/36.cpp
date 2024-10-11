#include <iostream.h>
class cls {
    int x;

public:
    cls(int i) { x = i; }
    int set_x(int i)
    {
        int y = x;
        x = i;
        return y;
    }
    int get_x() { return x; }
};
int main()
{
    cls* p = new cls[10]; //(1)
    int i = 0;
    for (; i < 10; i++)
        p[i].set_x(i);
    for (i = 0; i < 10; i++)
        cout << p[i].get_x();
    return 0;
}
