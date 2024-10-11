#include <iostream.h>
class cls1 {
protected:
    int x;

public:
    cls1() { x = 13; }
};
class cls2 : public cls1 {
    int y;

public:
    cls2() { y = 15; }
    int f(cls2 ob) { return (ob.x + ob.y); }
};
int main()
{
    cls2 ob;
    cout << ob.f(ob);
    return 0;
}