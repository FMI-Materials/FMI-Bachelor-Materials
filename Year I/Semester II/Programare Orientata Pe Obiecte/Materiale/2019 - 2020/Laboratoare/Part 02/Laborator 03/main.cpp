#include <iostream>

#include "String.h"

using namespace std;

int main() {
    String s1("abc");
    cout<<s1.getInfo()<<'\n';
    String s2("abca");
    cout<<(s1==s2)<<'\n';
    s1.change(1)='x';
    cout<<s1.getInfo()<<'\n';
    String s3(s1);
    s3.change(2) = 'y';
    cout<<s3.getInfo()<<'\n';
    s3 = s1;
    cout<<s3.getInfo()<<'\n';
    s3 = s1 = s2;
    cout<<s3.getInfo()<<'\n';
    return 0;
}
