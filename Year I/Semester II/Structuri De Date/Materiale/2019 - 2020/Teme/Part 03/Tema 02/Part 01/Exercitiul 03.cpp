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
void pop ()
{
    stiva * bob;
    bob=top;
    if(top)

    {   top=top->next;
        delete bob;
    }


}

int main()
{
    int tarusi[100],i,n;
    cout<<"n= ";
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cout<<"tarusi["<<i<<"]= ";
        cin>>tarusi[i];
    }
    for(i=1;i<=n;i++)
    {
        if(top && tarusi[i]==top->info)
            pop();
        else
            push(tarusi[i]);
    }

    if(top)
        cout<<"configuratie invalida";
    else
        cout<<"configuratie valida";
    return 0;

}
