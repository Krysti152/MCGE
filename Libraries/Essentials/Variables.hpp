#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <map>
#include <vector>
#include <functional>


#include <MCGE/Essentials/Objects/Headers/InputHandler.hpp>
#include <MCGE/Essentials/Objects/Headers/Camera.hpp>
#include <MCGE/Essentials/Objects/Headers/Path.hpp>
#include <MCGE/Essentials/Objects/Headers/KinematicBody.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>
#include <MCGE/Essentials/Objects/Headers/RenderBuffer.hpp>
#include <MCGE/Essentials/Objects/Headers/Timer.hpp>




int SCREEN_WIDTH;
int SCREEN_HEIGHT;
std::string NAME;
bool IS_FULLSCREEN;
bool IS_RUNNING;
int FRAME_RATE;
sf::RenderWindow WINDOW;
gm::RenderBuffer RENDER_BUFFER;

sf::Font MAIN_FONT;
std::map<std::string, sf::Texture> TEXTURES;

sf::Event EVENT;
sf::VideoMode VIDEO_MODE(SCREEN_WIDTH,SCREEN_HEIGHT);

// DELTA in miliseconds, to get in seconds use calcDelta()
float DELTA;

gm::InputHandler INPUT;

gm::Camera CAMERA;


gm::Path PATH;

std::vector<gm::GameObject> GAMEOBJECTS;
std::vector<gm::ob_data> OBJECTS;

std::vector<gm::StaticBody*> STATIC_BODIES;
std::vector<gm::KinematicBody*> KINEMATIC_BODIES;
std::vector<gm::Timer> TIMERS;

std::map<std::string, std::function<void ()>> signals = {};

const std::vector<std::string> ob_types = {
    //0
    "GameObject",
    //1
    "Animation",
    //2
    "Animator",
    //3
    "Tileset",
    //4
    "KinematicBody",
    //5
    "StaticBody",
    //6
    "Body",
    //7
    "CollisionShape",
    //8
    "GUI",
    //9
    "Canvas",
    //10
    "Constainer",
    //11
    "Image",
    //12
    "Panel",
    //13
    "InputHandler",
    //14
    "Timer"
};