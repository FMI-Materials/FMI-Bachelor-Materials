#include <fstream>
#include <queue>

using namespace std;

ifstream in("heap.in");
ofstream out("heap.out");

int main()
{
    ios_base::sync_with_stdio(0);
    in.tie(0), out.tie(0);
    int N;
    in >> N;
    priority_queue<int> Q;

    while(N--)
    {
        int op;
        in >> op;
        if(op == 1)
        {
            int x;
            in >> x;
            Q.push(x);
        }
        else
        {
            out << Q.top() << '\n';
            Q.pop();
        }
    }
    return 0;
}