#include<iostream>
using namespace std;
struct coada
{
    int info;
    coada *next, *prev;
};
coada *l, *r;
void push_left(int x)
{
    coada *nou;
    //merge
    if (l==NULL)
    {
        nou=new coada;
        nou->info=x;
        nou->next=NULL;
        nou->prev=NULL;
        l=r=nou;

    }
    else
    {
        nou=new coada;
        nou->info=x;
        nou->next=l;
        nou->prev=NULL;
        l=nou;
    }

}
void push_right(int x)
{
    coada *nou;
    //merge
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
int pop_left ()
{
    coada * bob;
    //nu merge
    bob=l;
    int gigel=-1;
    if(l-r==0)
    {
        gigel=bob->info;
        l=r=NULL;
        delete bob;
    }
    else
    if(l)

    {
        gigel=bob->info;

        l=l->next;
        l->prev=NULL;
        delete bob;
    }
    return gigel;

}
int pop_right()
{
    coada *p;
    int gigel=-1;
    p=r;
    if(p)
    {
        gigel=p->info;
        p=p->prev;
        p->next=NULL;
        delete r;
        r=p;

    }
    return gigel;

}
void af ()
{
    if (l==NULL)
    {
        cout<<"lista vida";
    }
    //trebuie o copie a lui prim altfel se face NULL dupa fiecare afisare
    coada *p;
    p=l;
    while (p!=NULL)
    {
        cout<<p->info<<" ";
        p=p->next;
    }
    cout<<endl;

}
int main()
{/*
    push_left (1);
     push_right( 2);
     af();
    cout<<  pop_right()<<endl;
    cout<<  pop_left()<<endl;
       push_right (3);
       af();
       */
       cout<<"lets see"<<endl;
    push_left(1);
    push_right(2);
    cout<<pop_right();
    cout<<pop_left();
    push_right(3);
    cout<<pop_right();
}
