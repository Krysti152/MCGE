//running by MeowCat Game Engine v1.2
//COMPILE THIS FILE

#include <MCGE/engine.hpp>

#ifndef MAIN_CPP
#define MAIN_CPP

// #include "assets/scripts/example.hpp"


// called before WINDOW is created
void awake() {
    NAME = "TestTESTOWY";
    
}

// called before first frame
void start() {
    
}
// called every frame
void update() {

}

int main() {



    gm::START(update,start,awake);

    return 0;
}

#endif