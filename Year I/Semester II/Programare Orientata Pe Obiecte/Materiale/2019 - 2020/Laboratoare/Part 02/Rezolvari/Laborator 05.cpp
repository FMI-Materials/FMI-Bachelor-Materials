#include <iostream>
#include <vector>
#include <string>

using namespace std;

class B1
{
private:
    int v1, v2;
public:
    B1(int v1, int v2):v1(v1), v2(v2) {}
    friend ostream& operator << (ostream& out, const B1& other){
        out << other.v1 << ' ' << other.v2 << '\n';
        return out;
    }
};

class D: public B1{
    int t1, t2;
public:
    D(): B1(-3, -5), t1(10), t2(20){}
};

class Person{
protected:
    int age;
    const string nume;
    double height;
    bool hasLicense;

public:
    Person(int age=0, string nume="", double height=0, bool hasLicense=0):age(age), nume(nume), height(height), hasLicense(hasLicense){}

    friend ostream& operator<<(ostream& out, const Person &ob){
        out<<ob.age<<" "<<ob.nume<<" "<<ob.height<<" "<<ob.hasLicense;
        return out;
    }
};

class Programmer: virtual public Person{
protected:
    int linesOfCode;
public:
    Programmer(int a=0, string n="", double h=0, bool l=0, int ln=0):Person(a, n, h, l), linesOfCode(ln){}

    friend ostream& operator<<(ostream& out, const Programmer &ob){
        out<<static_cast<Person>(ob);
        out<<" "<<ob.linesOfCode;
        return out;
    }
};

class Bucatar: virtual public Person{
protected:
    vector <string> retete;
public:
    Bucatar(int a=0, string n="", double h=0, bool l=0, vector <string> v ={}):Person(a, n, h, l), retete(v){}
    friend ostream& operator<<(ostream& out, const Bucatar &ob){
        out<<static_cast<Person>(ob);
        for(auto x: ob.retete)
            out<<" "<<x;
        return out;
    }
};

class ProgramatorBucatar : public Programmer, public Bucatar {
private:

public:
    ProgramatorBucatar(int a=0, string n="", double h=0, bool l=0, int ln=0, vector<string> v={} ) : Bucatar(a,n,h,l,v), Programmer(a,n,h,l,ln) {}

    friend ostream& operator<<(ostream& out, const ProgramatorBucatar &ob){
        out << ob.Bucatar::age << " " << ob.nume << " " << ob.height << " " << ob.hasLicense << " " << ob.linesOfCode << endl;
        return out;
    }
};

int main(){
    Person P(19, "Delia", 1.68, 1);
    Programmer infoarenaGod(19, "Tifui", 1.65, 1, 1e9);
    Bucatar b(19, "Tifui", 1.65, 1, vector<string>({"lasagnia"}));
    //cout<<infoarenaGod;
    //cout<<b;

    //cout << endl;

    ProgramatorBucatar a(20,"James",1.8,1,10000, vector<string>({"Hello"}));
    cout << a;
    //cout << sizeof(Person) << " " << sizeof(Programmer) << " " << sizeof(Bucatar) << " " << sizeof(ProgramatorBucatar);
    return 0;
}
