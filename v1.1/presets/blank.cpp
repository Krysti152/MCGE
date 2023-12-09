//running by MeowCat Game Engine
//COMPILE THIS FILE

#include <MCGE/engine.hpp>

gm::Game main_game;

//#include "assets/scripts/example_script.hpp"

// called before first frame
void start() {

}
// called every frame
void update() {

}

int main() {

    main_game.setFrameRate(60);
    main_game.setResolution(1280,720);



    main_game.awake();
    main_game.start(update,start);

    return 0;
}