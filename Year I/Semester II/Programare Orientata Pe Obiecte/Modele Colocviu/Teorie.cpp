#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using str = std::string;

/* ---------------Exceptii-----------------*/
class app_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class value_error : public app_error
{
    using app_error::app_error;
};

// throw value_error("mesaj")


/* ---------------Derivare-----------------*/
static int id_max => int Baza::id_max = 0;
const int id;

class Baza
{
    //variabile
    
protected:
    Baza(const Baza& o) = default;
    Baza& operator=(const Baza& o) = default;
    virtual void read(std::istream& is);
    virtual void print(std::ostream& os) const;

public:
    virtual ~Baza() = default;
    virtual std::shared_ptr<Baza> clone() const = 0;

    friend std::istream& operator>>(std::istream& is, Baza& ob)
    {
        ob.read(is);
        return is;
    }

    friend std::ostream& operator>>(std::ostream& os, const Baza& ob)
    {
        ob.print(os);
        return os;
    }
};

void Baza::read(std::istream& is)
{
    // is >>
}

void Baza::print(std::ostream& os) const
{
    // os <<
}

class Derivata : public Baza
{
    // variabile

public:
    // Constructors
    Derivata(/* arguments */);
    Derivata(const Derivata& o) : Baza(o) {};

    std::shared_ptr<Baza> clone() const override
    {
        return std::make_shared<Derivata>(*this);
    }
};

void Derivata::read(std::istream& is)
{
    Baza::read(is);
}

void Derivata::print(std::ostream& os) const
{
    Baza::print(os);
}


/* ---------------Singleton-----------------*/
class application
{
    application() = default;

public:
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& get_app()
    {
        static application app;
        return app;
    }
};

auto& x = application::get_app();


/* ---------------Factory-----------------*/
class scaun
{
    int pret;
    bool sold;
    str material;

public:
    scaun(int pret_, bool sold_, str material_) : pret(pret_), sold(sold_), material(material_) {};
};

class scaun_factory 
{
public:
    static scaun taburet() { return scaun(4, false, "lemn"); }
    static scaun taburet_simplu() { return scaun(3, false, "lemn"); }
    static scaun scaun_de_lemn() { return scaun(4, true, "lemn"); }
    static scaun scaun_de_metal() { return scaun(4, true, "metal"); }
    static scaun scaun_modern() { return scaun(2, true, "metal"); }
};

scaun s = scaun_factory::taburet();



/* ---------------Extra-----------------*/
// in afara clasei
friend bool operator<(const X& l, const X& r)
{
    return blabla;
}

// in clasa
bool operator<(const X& r)
{
    return this->atribut < r.atribut;
}

// pentru shared_ptr<>
bool ComparareProduse(const std::shared_ptr<X>& p1, const std::shared_ptr<X>& p2)
{
    return *p1 < *p2;
}
std::sort(produse.begin(), produse.end(), ComparareProduse);

// in afara clasei
friend bool operator==(const X& lhs, const X& rhs) 
{
    return blabla;
}

// in clasa
bool operator==(const X& rhs)
{
    return this->atribut == rhs.atribut;
}

// prefix increment
X& operator++()
{
    // actual increment takes place here
    return *this; // return new value by reference
}

// postfix increment
X operator++(int)
{
    X old = *this; // copy old value
    operator++();  // prefix increment
    return old;    // return old value
}

// Operatori aritmetici
X operator+(const X& other) 
{
    return X(valoare + other.valoare);
}

X& operator+=(const X& rhs) // compound assignment (does not need to be a member,
{                           // but often is, to modify the private members)
    /* addition of rhs to *this takes place here */
    return *this; // return the result by reference
}