
// MeowCat Game Engine v1.2

#pragma once
#ifndef MCGE_HPP
#define MCGE_HPP

#include <chrono>
#include <thread>
#include <unistd.h>
#include <functional>

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <filesystem>
#include <cmath>
#include <fstream>
#include <sstream>

#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <MCGE/Essentials/Variables.hpp>

#include <MCGE/Essentials/Functions.hpp>
#include <MCGE/objects.hpp>



using namespace std::chrono;
using namespace std;




namespace gm {
    
    

    void gm::CollisionShape::render() {
        if (this->is_active == false) {
            return;
        }
        if (this->is_circle) {
            WINDOW.draw(this->circle);
            return;
        }
        WINDOW.draw(this->rect);
    }

    void createObject(gm::GameObject _gm_ob) {
        GAMEOBJECTS.push_back(_gm_ob);
    }

    gm::Body getBody(string _name) {
        gm::Body body;
        body.name = "NULL";
        for (int i = 0; i < KINEMATIC_BODIES.size(); i++) {
            if (KINEMATIC_BODIES[i]->name == _name) {
                body = *KINEMATIC_BODIES[i];
            }
        }
        for (int i = 0; i < STATIC_BODIES.size(); i++) {
            if (STATIC_BODIES[i]->name == _name) {
                body = *STATIC_BODIES[i];
            }
        }
        return body;
    }

    gm::GameObject getObject(string _name) {
        // GAMEOBJECTS
        
        for (const gm::GameObject& _gm_ob : GAMEOBJECTS) {
            if (_gm_ob.name == _name) {
                return _gm_ob;
            }
        }
    }

    // auto getObject(int _ob_type,string _name) {

    //     // if (_id < 0 || _id >= GAMEOBJECTS.size()) {
    //     //     return;
    //     // }
    //     // int type_id = GAMEOBJECTS[_id].node_type_id;
    //     switch(_ob_type) {
    //         // GAMEOBJECT
    //         case 0:
    //             for (const gm::GameObject& _gm_ob : GAMEOBJECTS) {
    //                 if (_gm_ob.name == _name) {
    //                     return &_gm_ob;
    //                 }
    //             }
    //             break;
    //         case 1:
    //             break;
    //         case 2:
    //             break;
    //         // TILESET
    //         case 3:
    //             // for (const gm::Tileset& _ts : TILESETS) {
    //             //     if (_ts.name == _name) {
    //             //         return &_ts;
    //             //     }
    //             // }
    //             break;
    //         case 4:
    //             break;
    //         case 5:
    //             break;
    //         case 6:
    //             break;
    //         case 7:
    //             break;
    //     }
    //     // return true;
    //     // for (const gm::GameObject& gm : GAMEOBJECTS) {

    //     // }
    // }
    

    void UPDATE() {
        INPUT.update();
        WINDOW.setView(CAMERA.view);
        // for (int i = 0; i < draw_buffer.size(); i++) {
        //     WINDOW.draw(draw_buffer[i]);
        // }
        CAMERA.mouse_pos = sf::Mouse::getPosition(WINDOW);


        // for (const gm::KinematicBody* kin : KINEMATIC_BODIES) {
        //     // cout<<ob_types[kin->node_type_id]<<endl;
        //     kin->move_and_collide();
        // }

        // render();

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
        CAMERA.init(SCREEN_WIDTH, SCREEN_HEIGHT);
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

        std::cout<<"Connected Signals: "<<std::endl;
        for (const auto& [signal, func] : signals) {
            std::cout<<signal<<std::endl;
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