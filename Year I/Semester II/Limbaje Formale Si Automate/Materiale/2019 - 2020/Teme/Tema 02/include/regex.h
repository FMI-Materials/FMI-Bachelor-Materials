#include <iostream>
#include <string>

#ifndef TEMA2_REGEX_H
#define TEMA2_REGEX_H

class REGEX{
    std::string syntax;
    std::string minimize_string(std::string);
public:
    REGEX(std::string);

    void minimize();

    friend std::istream& operator>>(std::istream&, REGEX&);
    friend std::ostream& operator<<(std::ostream&, const REGEX&);
};

#endif //TEMA2_REGEX_H
