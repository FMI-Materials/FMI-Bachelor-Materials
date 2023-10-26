#include <iostream>
#include <vector>

using namespace std;

#include "vector.h"

class test{
private:
    static unsigned m;
public:

    test(){
        m++;
    }

    ~test(){
        m--;
    }

    static int get_m(){
        return m;
    }

};

unsigned test::m = 0;

int main() {
    Vector a(std::vector<int>({1, 3, 1, 5}));
    //a.afisare();

    //cin>>a;
    cout<<a<<'\n';
    //a=a+1;
    //a+=2;
    a++;
    cout<<a<<'\n';
    a[2] = 88;
    cout<<a;
    return 0;
}
