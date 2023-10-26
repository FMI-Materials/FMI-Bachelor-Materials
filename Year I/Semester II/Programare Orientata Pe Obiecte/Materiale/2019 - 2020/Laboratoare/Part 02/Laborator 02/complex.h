#ifndef LAB2_COMPLEX_H

class Complex{
private:
    int r, i;
    /** Encapsularea - obligatorie ( variabile in private, get-uri si set-uri in public ) **/
public:

    Complex();
    Complex(int, int = 0);
    Complex(const Complex&);

    inline int get_i() const { return i; }
    inline int get_r() const { return r; }

    void afisare() const;
    std::string to_String() const;
};

#endif
