#ifndef CHESSAI_EXCEPTION_H
#define CHESSAI_EXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

class Exception: public std::exception{
    std::string error_name;
public:
    Exception(std::string _error_name): error_name(_error_name){}
    ~Exception() throw() {}

    virtual const char* what() throw(){
        return error_name.c_str();
    }
};

#endif //CHESSAI_EXCEPTION_H
