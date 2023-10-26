#include <iostream>

using namespace std;

/*****  Use move semantics to improve performance  *****/

class Test
{
    int x;
    int *v;
public:
    Test(){x = 123; v = new int[3]; v[0] = 4; v[1] = 5; v[2] = 6;}
    ~Test(){x = -789; delete[] v; v = NULL;}
    void afis() {cout<<x<<" "; if (v == NULL) cout<<"NULL\n"; else cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<"\n";}
/// copy
    Test(Test& ob){ cout<<"\nCopy constructor  ";
        x = ob.x; v = new int[3]; for(int i = 0; i<3; i++) v[i] = ob.v[i];}
    Test& operator= (Test& ob)
    {
        if (this != &ob)
        {
            cout<<"\nCopy asignment  ";
            x = ob.x; v = new int[3]; for(int i = 0; i<3; i++) v[i] = ob.v[i];
        }
        return *this;
    }
/// move
    Test(Test&& ob): x(0), v(NULL) { cout<<"\nMove constructor  ";
                    x = ob.x; v = ob.v;
                    ob.x = 0; ob.v = NULL;
                    }
    Test& operator= (Test&& ob)
    {
        if (this != &ob)
        {
            cout<<"\nMove asignment  ";
            delete[] v;
            x = ob.x; v = ob.v;
                    ob.x = 0; ob.v = NULL;
        }
        return *this;
    }
};
int main()
{
    Test A, B(A);
    B.afis();
    Test C;
    C = B;
    C.afis();

    Test D (move(A));
    D.afis();
    cout<<"\nDupa move constructor A devine\n";
    A.afis();

///    Test E = move(A);   /// Atentie, A a fost modificat anterior
    Test E = move(B);
    E.afis();
    cout<<"\nDupa move constructor B devine\n";
    B.afis();

    Test F;
    F = move(C);
    F.afis();
    cout<<"\nDupa move asignment C devine\n";
    C.afis();

    return 0;
}

/**** pentru a evita codul redundant, se poate apela move asignment in interiorul move constructor ****/

/*   MemoryBlock(MemoryBlock&& other)
   : _data(nullptr)
   , _length(0)
{
   *this = std::move(other);
}*/
