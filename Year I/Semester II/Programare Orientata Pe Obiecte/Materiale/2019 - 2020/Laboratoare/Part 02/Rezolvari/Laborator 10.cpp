#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

template <class T>
class Exemplu
{
    static int i;

public:
    Exemplu()
    {
        i++;
        cout << i << '\n';
    }
    static int get_i()
    {
        return i;
    }
};
template <class T>
int Exemplu<T>::i = 0;

template <class A>
std::vector<A> MySort(std::vector<A> v)
{
    std::sort(v.begin(), v.end());
    return v;
}

template <>
std::vector<char> MySort<char>(std::vector<char> v){
    int f[255];
    memset(f, 0, sizeof(f));

    for(char i : v)
        f[i]++;

    std::vector<char> sorted;
    for(int i = 0; i < 255; i++)
        while (f[i]--)
            sorted.push_back(i);

    return sorted;
}

int main()
{
    Exemplu<int> a;
    Exemplu<int> b;
    Exemplu<char> c;
    cout << Exemplu<int>::get_i() << '\n';
    cout << Exemplu<char>::get_i() << '\n';
    return 0;
}
