//sapt 5 deadline
//varf stiva ---------baza stiva=> pop sterge elementele de la inceput p=p->next delete
//int pop sa mi zica ce a scos ptim=top si retinem gigel ca sa returnez valoarea
//tarusii conectati sunt cei care au aceeasi eticheta
//avem 2 functii psuh si pop la intrare etc
#include<iostream>
using namespace std;
struct stiva
{
    int info;
    stiva *next;
};
stiva *top;
void push(int x)
{
    stiva *nou;
    if (top==NULL)
    {
        nou=new stiva;
        nou->info=x;
        nou->next=NULL;
        top=nou;

    }
    else
    {
        nou=new stiva;
        nou->info=x;
        nou->next=top;
        top=nou;
    }

}
int pop ()
{
    stiva * bob;
    bob=top;
    int gigel=-1;
    if(top)

    {   top=top->next;
        gigel=bob->info;
        delete bob;
    }
    return gigel;

}

void af ()
{
    if (top==NULL)
    {
        cout<<"lista vida";
    }
    //trebuie o copie a lui prim altfel se face NULL dupa fiecare afisare
    stiva *p;
    p=top;
    while (p!=NULL)
    {
        cout<<p->info<<" ";
        p=p->next;
    }
    cout<<endl;

}
int main()
{
    push (1);
     cout<<pop();
     push (2);
     push(3);
     cout<<endl;
     af();


}
