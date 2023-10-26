//
// Created by Darius Buhai on 3/5/20.
//

#include <iostream>
#include <cstring>
#include "String.h"

String::String(): len(0), info(new char('\0')){}
String::String(char *i): len(strlen(i)){
    info = new char[len+1];
    strcpy(info, i);
}
String::String(const String &other): len(other.len){
    info = new char[len+1];
    for(int i=0;i<len;i++)
        info[i] = other.info[i];
}
String::String(std::string str): len(str.size()){
    info = new char[len+1];
    for(int i=0;i<len;i++)
        info[i] = str[i];
    info[len] = '\0';
}

String String::operator=(const String &other){
    if(&other != this){
        delete [] info;
        len = other.len;
        info = new char[len-1];
        strcpy(info, other.info);
        return *this;
    }
}
bool String::operator==(const String &other) const{
    if(other.len!=this->len)
        return false;
    for(int i=0;i<this->len;i++)
        if(other.info[i]!=this->info[i])
            return false;
    return true;
}

String String::operator=(String &&other){
    len = other.len;
    other.len = 0;
    info = other.info;
    other.info = nullptr;
    return *this;
}

void String::change(unsigned pos, char c){
    if(pos>=len)
        return;
    info[pos] = c;
}

char& String::change(unsigned pos){
    if(pos<len)
        return info[pos];
}

char* String::getInfo() const{
    return this->info;
}