#include <iostream>
#include "complex.h"

/// Tema - Proiect mare
/// De venit cu ideea
/// De facut utilizand sfml, qt ...

/**
 * Preproccesor directives:
 * 1. Includes <>, ".h"
 * 2. Macrouri (#define)
 * 3. Conditional directives: #ifndef
 * 4. Alte directive
 *
 * cod -precompilat-> cod -compilat-> obj
 * main.cpp -> main.o       |
 * complex.cpp -> complex.o | -linking-> .exe
 */

using namespace std;



int main() {
    Complex c = Complex(6); /// Copy elision
    c.afisare();
    return 0;
}
