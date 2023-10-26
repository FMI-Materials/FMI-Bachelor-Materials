#include<iostream>
using namespace std;
struct nod
{
    int info;
    nod *next;
};
nod *prim, *ultim, *nou;
void adi(int x)
{
    if (prim==NULL)
    {
        nou=new nod;
        nou->info=x;
        nou->next=NULL;
        ultim=prim=nou;

    }
    else
    {
        nou=new nod;
        nou->info=x;
        nou->next=prim;
        prim=nou;
    }
}
void adf(int x)
{
    if (prim==NULL)
    {
        nou=new nod;
        nou->info=x;
        nou->next=NULL;
        ultim=prim=nou;
    }
    else
    {
       nou=new nod;
       nou->info=x;
       nou->next=NULL;
       ultim->next=nou;
       ultim=nou;
    }
}
int cv(int x)
{
    nod *p;
    p=prim;
    int contor;
    for(contor=1; p!=NULL;contor++, p=p->next)
        if(p->info==x)
            return contor;
    return -1;
}
int cp(int poz)
{
    nod *p;
    p=prim;
    int i;
    for(i=1;i<poz;i++)
        p=p->next;
    if (p==NULL)
        return -1;
    else
        return p->info;
}
void iv(int val, int elem)
{
    nod *p;
    for(p=prim; p!=NULL;p=p->next)
        if(p->info==val)
    {
        nou=new nod;
        nou->info=elem;
        if (p->next==NULL)
        {
            nou->next=NULL;
            ultim->next=nou;
            ultim=nou;
        }
        else
        {
            nou->next=p->next;
            p->next=nou;

        }
        break;

    }

}
void ip( int poz, int elem)
{
    nod *p;
    int i;
    if(poz==0)
    {
        nou=new nod;
        nou->info=elem;
        nou->next=prim;
        prim=nou;
    }
    else
        for(p=prim,i=1; p!=NULL;p=p->next, i++)
            if(i==poz)
    {
            nou=new nod;
            nou->info=elem;
            if(p->next==NULL)
            {
                nou->next=NULL;
                ultim->next=nou;
                ultim=nou;
            }
            else
            {
                nou->next=p->next;
                p->next=nou;

            }
        break;
    }
}
void af ()
{
    if (prim==NULL)
    {
        cout<<"lista vida";
    }
    //trebuie o copie a lui prim altfel se face NULL dupa fiecare afisare
    nod *p;
    p=prim;
    while (p!=NULL)
    {
        cout<<p->info<<" ";
        p=p->next;
    }
    cout<<endl;

}
void sv(int x)
{
    nod *p;

    for (p=prim; p!=NULL;p=p->next)
        if(p->info==x)
    {
        if(p==prim)
        {
            prim=prim->next;
            delete p;
        }
        else
            if(p->next==NULL)
        {
            nod *a;
            a=prim ;
            while(a->next->next!=NULL)
                a=a->next;
            a->next=NULL;
            ultim=a;
            delete p;
        }
        else
        {
            nod *a;
            a=prim ;
            while(a->next!=p)
                a=a->next;
            a->next=p->next;
            delete p;
        }
        break;
    }

}
void sp(int poz)
{
     nod *p;
     int i;


    for (p=prim, i=1; p!=NULL;p=p->next, i++)
        if(poz==i)
    {
        if(poz==1)
        {
            prim=prim->next;
            delete p;
        }
        else
            if(p->next==NULL)
        {
            nod *a;
            a=prim ;
            while(a->next->next!=NULL)
                a=a->next;
            a->next=NULL;
            ultim=a;
            delete p;
        }
        else
        {
            nod *a;
            a=prim ;
            while(a->next!=p)
                a=a->next;
            a->next=p->next;
            delete p;
        }
        break;
    }
}
int main()
{

    af();
    adi(1);
    adi(2);
    adi(3);
    af();
    adf(4);
    af();
    cout<<cv(5)<<endl;
    cout<<cv(1)<<endl;
    cout<<cp(5)<<endl;
    cout<<cp(3)<<endl;
    sp(1);
    af();
    sp(1);
    af();
    sv(4);
    af();
    adf(5);
    af();
    sv(1);
    sp(1);
    af();
    adf(8);
    af();

    return 0;

}
