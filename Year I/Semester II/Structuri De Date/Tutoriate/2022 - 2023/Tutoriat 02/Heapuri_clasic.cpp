#include <fstream>
#include <queue>

using namespace std;

ifstream in("heap.in");
ofstream out("heap.out");

const int Nmax = 250005;
int Heap[Nmax];
int heapSize;

void Insert(int x)
{
    heapSize++;
    Heap[heapSize] = x;

    int pozNod = heapSize;

    while(pozNod > 1 && Heap[pozNod] > Heap[pozNod / 2])
    {
        swap(Heap[pozNod], Heap[pozNod / 2]);
        pozNod /= 2;
    }
}

int GetMax()
{
    return Heap[1];
}

void Delete()
{
    swap(Heap[1], Heap[heapSize]);
    heapSize--;

    int currPoz = 1;
    int nextPoz = -1;

    while(nextPoz)
    {
        int left = 2 * currPoz, right = 2 * currPoz + 1;
        int nextNod = Heap[currPoz];
        nextPoz = 0;

        if(left <= heapSize && nextNod < Heap[left])
        {
            nextNod = Heap[left];
            nextPoz = left;
        }

        if(right <= heapSize && nextNod < Heap[right])
        {
            nextNod = Heap[right];
            nextPoz = right;
        }

        if(nextPoz)
        {
            swap(Heap[currPoz], Heap[nextPoz]);
            currPoz = nextPoz;
        }
    }
}

int main()
{

    int N;
    in >> N;
    int Heap[N + 1];
    int heapSize = 0;
    while(N--)
    {
        int op;
        in >> op;
        if(op == 1)
        {
            int x;
            in >> x;
            Insert(x);
        }
        else
        {
            int top = GetMax();
            out << top << '\n';
            Delete();
        }
    }
    return 0;
}
