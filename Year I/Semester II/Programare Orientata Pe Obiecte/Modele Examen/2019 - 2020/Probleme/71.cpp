#include <iostream.h>
class cls1 {
    int x;

public:
    cls1() { x = 13; }
    int g()
    {
        static int i;
        i++;
        return (i + x);
    }
};
class cls2 {
    int x;

public:
    cls2() { x = 27; }
    cls1& f()
    {
        static cls1 ob;
        return ob;
    }
};
int main()
{
    cls2 ob;
    cout << ob.f().g();
    return 0;
}