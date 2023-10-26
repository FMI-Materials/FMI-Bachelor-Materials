//
// Created by Darius Buhai on 3/5/20.
//

#ifndef LAB3_STRING_H
#define LAB3_STRING_H

class String{
private:
    size_t len;
    char * info;
public:
    String();
    String(char *);
    String(const String &);
    String(std::string str);
    String operator=(const String&);
    String operator=(String &&);

    bool operator==(const String &) const;
    void change(unsigned pos, char c);
    char& change(unsigned pos);
    char* getInfo() const;
};


#endif //LAB3_STRING_H
