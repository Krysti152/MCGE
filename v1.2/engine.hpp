
// MeowCat Game Engine v1.2

#pragma once
#ifndef MCGE_HPP
#define MCGE_HPP

#include <chrono>
#include <thread>
#include <unistd.h>
#include <functional>

#include <MCGE/Libraries.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Drawable.hpp>


int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
std::string NAME = "GAMENAME";
bool IS_FULLSCREEN = false;
bool IS_RUNNING = false;
int FRAME_RATE = 60;
sf::Font MAIN_FONT;
std::map<std::string, sf::Texture> TEXTURES;


// DELTA in miliseconds, to get in seconds use calcDelta()
float DELTA;
sf::Event EVENT;
sf::VideoMode VIDEO_MODE(SCREEN_WIDTH,SCREEN_HEIGHT);
sf::RenderWindow WINDOW;

#include <MCGE/Functions.hpp>
#include <MCGE/objects.hpp>


using namespace std::chrono;
using namespace std;



// #include <MCGE/objects/Camera.hpp>

gm::Camera CAMERA = {SCREEN_WIDTH, SCREEN_HEIGHT};

gm::InputHandler INPUT;

gm::Path PATH;

gm::RenderBuffer RENDER_BUFFER;

vector<gm::GameObject> GAMEOBJECTS;
vector<gm::Sprite> SPRITES;

namespace gm {


    

    void UPDATE() {
        INPUT.update();
        WINDOW.setView(CAMERA.view);
        // for (int i = 0; i < draw_buffer.size(); i++) {
        //     WINDOW.draw(draw_buffer[i]);
        // }
        CAMERA.mouse_pos = sf::Mouse::getPosition(WINDOW);
    }

    void END() {
        // cout<<"Wygenerowano " << frames << " klatek.\n";
        // cout<<"Chodzilo przez "<<(float) (delta * frames) / 1000000<<" sekund.\n";
        cout<<"Shutting Down"<<endl;
    }


    void START(function<void ()> upd, function<void ()> str, function<void ()> awk) {

        auto ICON = sf::Image{};

        INPUT.name = "MainInput";

        

        cout<<"MeowCat Game Engine V1.2"<<endl;
        cout<<"----------"<<endl;
        cout<<"Preferences:"<<endl;
        loadPrefs();
        updateVideoMode();
        CAMERA = Camera{SCREEN_WIDTH, SCREEN_HEIGHT};
        cout<<"----------"<<endl;

        cout<<"Init:"<<endl;

        // if (ICON.loadFromFile("icon.png"))
        // {
        //     WINDOW.setIcon(ICON.getSize().x, ICON.getSize().y, ICON.getPixelsPtr());
        //     std::cout<<"Załadowano IKONĘ: assets/sprites/missing_texture.png"<<std::endl;
        // }





        // loadTexture("MISSING_TEXTURE", "assets/sprites/missing_texture.png");

        awk();


        cout<<"----------"<<endl;

        std::cout<<"Loaded TEXTURES in memory: "<<std::endl;
        for (const auto &[name,tex] : TEXTURES) {
            std::cout<<"- "<<name<<std::endl;
        }

        cout<<"----------"<<endl;


        std::cout<<NAME+":"<<std::endl;
        cout<<"Starting..."<<endl;
        calcDelta();
        IS_RUNNING = true;

        WINDOW.setFramerateLimit(FRAME_RATE);
        WINDOW.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), NAME, IS_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close);
        str();
        int frames = 0;
        while (IS_RUNNING) {
            while (WINDOW.isOpen()) {
                while (WINDOW.pollEvent(EVENT)) {
                    if (EVENT.type == sf::Event::Closed) {
                        WINDOW.close();
                        IS_RUNNING = false;
                    }
                }
                WINDOW.clear();
                auto start = high_resolution_clock::now();
                UPDATE();
                upd();
                frames++;
                WINDOW.display();
                auto stop = high_resolution_clock::now();
                auto dur = duration_cast<microseconds>(stop - start);
                if (dur.count() < DELTA) {
                    usleep(DELTA-dur.count());
                }
            }
            // IS_RUNNING = false;
        } 
        END();
    }

    float getDelta() {
        return DELTA/1000000;
    }

    sf::Vector2f vec_to_sf(gm::Vector2 _vec) {
        return sf::Vector2f{_vec.x,_vec.y};
    }


}

#endif