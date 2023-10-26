#include <iostream>

using namespace std;

class B{
    int n;
    int* i;
public:
    B(int n = 8): n(n), i(new int(55)){if(n == 0) throw n;}
    ~B(){cout << "DB"; }
};

int main()
{
    try{
        B b;
        B h(0);
        throw 8;
        B g;
    }catch(int i){
        cout << "DE : " << i <<'\n';
    }
    return 0;
}
