
#include <iostream>

using namespace std;
class Singletone{
private:
    static Singletone *obiect;
    string data;

    Singletone(){
        data="dd/mm/yyyy";
    }
public:
    static Singletone* getInstance(){
        if(!obiect)
            obiect=new Singletone();


        return obiect;
    }

    string getData(){return this->data;}
    void setData(string a) {this->data=a;}

};
Singletone* Singletone::obiect=0;
int main()
{
    Singletone *s=s->getInstance();
    cout<<s->getData();
    s->setData("19.04.2021");
    cout<<endl;
    cout<<s->getData();
    cout<<endl;
    Singletone *s2=s2->getInstance();
    cout<<s->getData();


    return 0;
}


