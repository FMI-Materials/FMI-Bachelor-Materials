#include <iostream.h>
class cls1 {
protected:
    int x;

public:
    cls1(int i = 10) { x = i; }
    int get_x() { return x; }
};
class cls2 : cls1 {
public:
    cls2(int i)
        : cls1(i)
    {
    }
};
int main()
{
    cls d(37);
    cout << d.get_x();
    return 0;
} 