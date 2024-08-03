#include <iostream>
#include <deque>
#include <vector>
#include <functional>
using namespace std;

template<class T, function<bool(T, T)> cmp_func>
class Heap
{
private:
    T *v;
    int n, nr_elem;
public:
    Heap(unsigned l){
        v = new T[l];
        n = l;
        nr_elem = 0;
    }

    Heap(Heap&& obj) {
        n = obj.n;
        nr_elem = obj.nr_elem;
        v = obj.v;
        obj.v = new T[1];
        obj.n = 1;
        obj.nr_elem = 0;
    }
    Heap(const Heap &oth)
    {
        v = new T[oth.n];
        n = oth.n;
        nr_elem = oth.nr_elem;
        for(int i = 0; i < n; ++i)
            v[i] = oth.v[i];
    }

    ~Heap()
    {
        delete[] v;
        n = nr_elem = 0;
    }
    std::vector<T> Asc(){
        Heap<T, cmp_func> aux_heap = *this;
        std::deque<T> res;
        std::vector<T> res_op;
        while(aux_heap.nr_elem>0)
            res.push_front(aux_heap.Pop());
        for(auto &el: res)
            res_op.push_back(el);
        return res_op;
    }

    void Push(T val)
    {
        if (nr_elem >= n) {
            T* P = new T[n * 2];
            for (int i = 0; i < nr_elem; ++i)
                P[i] = v[i];

            delete[] v;
            v = P;
            n *= 2;
        }

        v[nr_elem] = val;
        ++nr_elem;

        Up(nr_elem);
    }

    void Up(int poz)
    {
        if (poz == 0) return;
        if (!cmp_func(v[(poz + 1) / 2 - 1], v[poz])) {
            swap(v[(poz + 1) / 2 - 1], v[poz]);
            Up((poz + 1) / 2 - 1);
        }
    }

    void Down(int poz)
    {
        auto fiu_stang = [](int poz) {
            return poz * 2 + 1;
        };
        auto fiu_drept = [](int poz) {
            return poz * 2 + 2;
        };

        /// primul caz, nu am niciun fiu
        if (fiu_stang(poz) >= nr_elem)
            return;

        /// cazul 2: am un singur fiu
        if (fiu_drept(poz) == nr_elem) {
            if (cmp_func(v[fiu_stang(poz)], v[poz]))
                swap(v[poz], v[fiu_stang(poz)]);
        }
        else {
            /// ultimul caz: am ambii fii
            if (cmp_func(v[fiu_stang(poz)], v[poz]) &&
                cmp_func(v[fiu_stang(poz)], v[fiu_drept(poz)])) {
                swap(v[poz], v[fiu_stang(poz)]);
                Down(fiu_stang(poz));
            }
            else if (cmp_func(v[fiu_drept(poz)], v[poz])) {
                swap(v[poz], v[fiu_drept(poz)]);
                Down(fiu_drept(poz));
            }
        }
    }

    Heap(std::initializer_list<T> init) : Heap(init.size())
    {
        for (auto i : init)
            Push(i);
    }

    T Pop()
    {
        if (nr_elem == 0)
            throw std::runtime_error("No elements for pop");
        T ans = v[0];
        v[0] = v[nr_elem - 1];
        nr_elem--;
        Down(0);

        return ans;
    }
};

int main() {
    std::cout << "Hello World!\n";
}






