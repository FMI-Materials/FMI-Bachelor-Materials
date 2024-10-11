#include <iostream.h>
class cls1 {
public:
    int x;
    cls1(int i = 20) { x = i; }
};
class cls2 {
public:
    int y;
    cls2(int i = 30) { y = i; }
    operator cls1()
    {
        cls1 ob;
        ob.x = y;
        return ob;
    }
};
cls1 f(cls1 ob)
{
    ob.x++;
    return ob;
}
int main()
{
    cls1 ob1;
    f(ob1);
    cout << ob1.x;
    cls2 ob2;
    f(ob2);
    cout << ob2.y;
    return 0;
}