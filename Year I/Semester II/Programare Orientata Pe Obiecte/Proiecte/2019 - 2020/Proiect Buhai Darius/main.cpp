#include "include/draw.h"

using namespace std;

#if defined(_WIN32)
    #include "draw.cpp"
#endif

int main(){

    unique_ptr<Draw> drawPtr(Draw::getInstance());
    drawPtr->startGame();
    return 0;
}
