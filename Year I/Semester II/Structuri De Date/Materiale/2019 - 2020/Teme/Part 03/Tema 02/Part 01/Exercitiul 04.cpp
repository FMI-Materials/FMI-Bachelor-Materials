#include<iostream>
#include<fstream>
using namespace std;
struct coada
{
    int info;
    coada *next, *prev;
};

void push_right(int x, coada *&l, coada *&r)
{
    coada *nou;

    if (r==NULL)
    {
        nou=new coada;
        nou->info=x;
        nou->prev=NULL;
        nou->next=NULL;
        r=l=nou;
    }
    else
    {
       nou=new coada;
       nou->info=x;
       nou->next=NULL;
       nou->prev=r;
       r->next=nou;
       r=nou;
    }
}
void pop_left (coada *&l, coada *&r)
{
    coada * bob;
    bob=l;
    if(l-r==0)
    {

        l=r=NULL;
        delete bob;
    }
    else
    if(l)

    {

        l=l->next;
        l->prev=NULL;
        delete bob;
    }


}
int M[100][100];

int main()

{
    ifstream f("matrice.txt");
    int m,i,j,a,b;
    coada *l1=NULL, *r1=NULL,*l2=NULL,*r2=NULL;
    f>>m;
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)
                f>>M[i][j];
    f.close();

    int Marcator=1;
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)
            if(M[i][j]==1)
                if (!l1)
            {
                push_right(i,l1,r1);
                push_right(j,l2,r2);
                Marcator++;

            }
            else
            {


                while(l1)
                {
                    a=l1->info;
                    b=l2->info;

                    pop_left(l1,r1);
                    pop_left(l2,r2);

                    M[a][b]=Marcator;

                    if (M[a-1][b]==1)
                    {
                        push_right(a-1,l1,r1);
                        push_right(b,l2,r2);


                    }
                    if (M[a][b-1]==1)
                    {

                        push_right(a,l1,r1);
                        push_right(b-1,l2,r2);

                    }
                    if (M[a][b+1]==1)
                    {
                        push_right(a,l1,r1);
                        push_right(b+1,l2,r2);

                    }
                    if (M[a+1][b]==1)
                    {

                        push_right(a+1,l1,r1);
                        push_right(b,l2,r2);

                    }


                }

            }
        for(i=1;i<=m;i++){
            for(j=1;j<=m;j++)
                cout<<M[i][j]<<" ";
        cout<<endl;

        }
        return 0;
}

