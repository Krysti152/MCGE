
// MeowCat Game Engine v1.2

#pragma once
#ifndef MCGE_HPP
#define MCGE_HPP

#include <chrono>
#include <thread>
#include <unistd.h>
#include <functional>

#include <MCGE/Libraries.hpp>
// #include <SFML/Graphics/Font.hpp>
// #include <SFML/Graphics/Texture.hpp>
// #include <SFML/Graphics/RenderWindow.hpp>
// #include <SFML/Window/Event.hpp>
// #include <SFML/Window/VideoMode.hpp>
// #include <SFML/Graphics/Drawable.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>









#include <MCGE/Essentials/Functions.hpp>
#include <MCGE/Essentials/Objects.hpp>



using namespace std::chrono;
using namespace std;



// gm::RenderBuffer RENDER_BUFFER;



vector<gm::ob_data> OBJECTS;

vector<gm::Timer> TIMERS;

vector<gm::GameObject> GAMEOBJECTS;
vector<sf::Sprite> SPRITES;
vector<sf::RectangleShape> RECTANGLES;
vector<sf::CircleShape> CIRCLES;
vector<gm::Tileset> TILESETS;

struct Connection {
    int ob_id;
    std::string signal;
};

map<string, function<void ()>> signals = {};

vector<gm::StaticBody*> STATIC_BODIES;
vector<gm::KinematicBody*> KINEMATIC_BODIES;

vector<string> ob_types = {
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

namespace gm {


    void connect(string _signal,function<void ()> _connected) {
        signals[_signal] = _connected;
    }

    void emit_signal(std::string _signal) {
        signals[_signal]();
    }
    void gm::Timer::emit_signal(string _signal) {
        gm::emit_signal(_signal);   
    }

    void gm::GameObject::log(std::string _msg) {
        std::cout<<name + " (" + to_string(this->node_id) + "-" + ob_types[this->node_type_id] + "): " + _msg<<std::endl;
    }

    void gm::GameObject::init() {
        int new_id = rand() % 10001;
        for (int i = 0; i < OBJECTS.size(); i++) {
            if (OBJECTS[i].id == new_id) {
                this->init();
                std::cout<<"Powtarza sie"<<std::endl;
                return;
            }
        }
        this->node_id = new_id;
        OBJECTS.push_back(gm::ob_data{new_id, this->node_type_id});
    }

    void gm::KinematicBody::move_and_collide() {
        this->body_id = 0;
        this->colliding = {false,false,false,false};
        // For every Static bodies
        for (const gm::StaticBody* bodyB : STATIC_BODIES) {
            // For every my own collision shapes
            for (const gm::CollisionShape& shapeA : this->collisions) {
                // For every Static Body Collision Shapes
                for (const gm::CollisionShape& shapeB : bodyB->collisions) {
                    if (shapeA.is_circle != shapeB.is_circle) {
                        return;
                    }
                    if (shapeA.is_circle) {

                    } else {
                        // RECTANGLE
                        if (shapeA.transform.position.x + shapeA.size.x > shapeB.transform.position.x &&
                            shapeA.transform.position.x < shapeB.transform.position.x + shapeB.size.x &&
                            shapeA.transform.position.y + shapeA.size.y + this->velocity.y * gm::calcDelta() > shapeB.transform.position.y &&
                            shapeA.transform.position.y + this->velocity.y * gm::calcDelta() < shapeB.transform.position.y + shapeB.size.y
                        ) {
                            // this->velocity.y *= -1;
                            if (this->velocity.y > 0) {
                                this->collide(2);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            } else if (this->velocity.y < 0) {
                                this->collide(0);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            }
                            this->velocity.y = 0;
                        }
                        if (shapeA.transform.position.x + shapeA.size.x + this->velocity.x * gm::calcDelta() > shapeB.transform.position.x &&
                            shapeA.transform.position.x + this->velocity.x * gm::calcDelta() < shapeB.transform.position.x + shapeB.size.x &&
                            shapeA.transform.position.y + shapeA.size.y > shapeB.transform.position.y &&
                            shapeA.transform.position.y < shapeB.transform.position.y + shapeB.size.y
                        ) {
                            // this->velocity.x *= -1;
                            if (this->velocity.x > 0) {
                                this->collide(3);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            } else if (this->velocity.x < 0) {
                                this->collide(1);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            }
                            this->velocity.x = 0;
                        }

                    }
                }
            }
        }
        for (const gm::KinematicBody* bodyB : KINEMATIC_BODIES) {
            if (bodyB == this) {
                continue;
            }
            // For every my own collision shapes
            for (const gm::CollisionShape& shapeA : this->collisions) {
                // For every Static Body Collision Shapes
                for (const gm::CollisionShape& shapeB : bodyB->collisions) {
                    if (shapeA.is_circle != shapeB.is_circle) {
                        return;
                    }
                    if (shapeA.is_circle) {

                    } else {
                        // RECTANGLE
                        if (shapeA.transform.position.x + shapeA.size.x > shapeB.transform.position.x &&
                            shapeA.transform.position.x < shapeB.transform.position.x + shapeB.size.x &&
                            shapeA.transform.position.y + shapeA.size.y + this->velocity.y * gm::calcDelta() > shapeB.transform.position.y &&
                            shapeA.transform.position.y + this->velocity.y * gm::calcDelta() < shapeB.transform.position.y + shapeB.size.y
                        ) {
                            // this->velocity.y *= -1;
                            if (this->velocity.y > 0) {
                                this->collide(2);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            } else if (this->velocity.y < 0) {
                                this->collide(0);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            }
                            this->velocity.y = 0;
                        }
                        if (shapeA.transform.position.x + shapeA.size.x + this->velocity.x * gm::calcDelta() > shapeB.transform.position.x &&
                            shapeA.transform.position.x + this->velocity.x * gm::calcDelta() < shapeB.transform.position.x + shapeB.size.x &&
                            shapeA.transform.position.y + shapeA.size.y > shapeB.transform.position.y &&
                            shapeA.transform.position.y < shapeB.transform.position.y + shapeB.size.y
                        ) {
                            // this->velocity.x *= -1;
                            if (this->velocity.x > 0) {
                                this->collide(3);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            } else if (this->velocity.x < 0) {
                                this->collide(1);
                                this->body_id = shapeB.parent->node_id;
                                // this->log("Colliding with " + shapeB.parent->getName());
                            }
                            this->velocity.x = 0;
                        }

                    }
                }
            }
        }
            
        this->transform.position.x += this->velocity.x * gm::calcDelta();
        this->transform.position.y += this->velocity.y * gm::calcDelta();
        this->update();

            
    }

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

    void addTimer() {

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

    void render() {
        for (int _sid = 0; _sid < SPRITES.size(); _sid++) {
            WINDOW.draw(SPRITES[_sid]);
        }
    }
    

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