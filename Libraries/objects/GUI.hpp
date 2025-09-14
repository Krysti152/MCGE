#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>
#include <MCGE/Essentials/Objects/Headers/Camera.hpp>
// #include <MCGE/engine.hpp>

#ifndef GUI_HPP
#define GUI_HPP


namespace gm {
    

    class GUI : public gm::GameObject {
    private:
    public:
        gm::Vector2 margin;
        std::string relative = "TOP_LEFT";
        gm::GUI* gui_parent;
        gm::Vector2 size;

        std::map<std::string, gm::Vector2> anchors = {
            {"TOP_LEFT", gm::Vector2{0,0}},
            {"TOP_RIGHT", gm::Vector2{0,0}},
            {"BOTTOM_LEFT", gm::Vector2{0,0}},
            {"BOTTOM_RIGHT", gm::Vector2{0,0}},
            {"TOP_MIDDLE", gm::Vector2{0,0}},
            {"BOTTOM_MIDDLE", gm::Vector2{0,0}},
            {"LEFT_MIDDLE", gm::Vector2{0,0}},
            {"RIGHT_MIDDLE", gm::Vector2{0,0}},
        };


        GUI(gm::GUI* _parent) {
            gui_parent = _parent;

            if (node_type_id == 0) {
                node_type_id = 8;
            }
        }
        GUI() {
            if (node_type_id == 0) {
                node_type_id = 8;
            }
        }
        ~GUI() {

        }
        void update() {
            gm::GameObject::update();
            if (gui_parent != 0) {
                transform.setPosition(gui_parent->transform.getPosition());
                transform.position.x += gui_parent->anchors[relative].x + margin.x;
                transform.position.y += gui_parent->anchors[relative].y + margin.y;
            }
        }

        void set_size(int _x, int _y) {
            size = {_x,_y};
            update_anchors();
        }
        void set_size(gm::Vector2 _vec) {
            set_size(_vec.x,_vec.y);
        }

        void update_anchors() {
            anchors["TOP_LEFT"] = gm::Vector2{-size.x/2,-size.y/2};
            anchors["TOP_RIGHT"] = gm::Vector2{size.x/2,-size.y/2};
            anchors["BOTTOM_LEFT"] = gm::Vector2{-size.x/2,size.y/2};
            anchors["BOTTOM_RIGHT"] = gm::Vector2{size.x/2,size.y/2};
            anchors["MIDDLE"] = gm::Vector2{0,0};
            anchors["LEFT"] = gm::Vector2{-size.x/2,0.};
            anchors["RIGHT"] = gm::Vector2{size.x/2,0.};
            anchors["TOP"] = gm::Vector2{0.,-size.x/2};
            anchors["BOTTOM"] = gm::Vector2{0.,size.x/2};
            
        }
    };

    class Canvas : public gm::GUI
    {
    private:
    public:

        // sf::View resolution;

        gm::Camera* camera;

        

        void set_screen_size() {
            // resolution.setSize(camera->view.getSize());
            // size = {camera->view.getSize()};
            // update_anchors();
            gm::Vector2 cam_size = {camera->view.getSize()};
            set_size(cam_size);
        }

        Canvas(gm::Camera* _cam) {
            camera = _cam;
            if (node_type_id == 0) {
                node_type_id = 9;
            }
            
        }

        ~Canvas() {

        }

        void update() {
            gm::GameObject::update();
            transform.setPosition(camera->transform.getPosition());
        }

        
    };

    class Container : public gm::GUI {
    private:
    public:

        int spacing = 10;
        int cell_size = 32;
        bool horizontal = true;


        gm::Vector2 calc_pos(int _id) {
            gm::Vector2 new_vec;
            if (horizontal) {
                new_vec.x = transform.position.x + cell_size * _id + spacing * _id;
                new_vec.y = transform.position.y;
            } else {
                new_vec.x = transform.position.x;
                new_vec.y = transform.position.y + cell_size * _id + spacing * _id;
            }
            return new_vec;
        }

        // Container(gm::Canvas* _canvas)
        // : gm::GUI(_canvas) {
        //     subclass_name = "CONTAINER";
        // }
        Container(gm::GUI* _parent) 
        : gm::GUI(_parent) {
            if (node_type_id == 0) {
                node_type_id = 12;
            }
        }
        ~Container() {};

        void update() {
            gm::GUI::update();
            
        }

    };

    class Image : public gm::GUI {
    private:
    public:
        sf::Sprite image;
        void update() {
            gm::GUI::update();
            // if (is_active) {
            //     WINDOW.draw(image);
            // }
            image.setPosition(transform.getPosition().to_sf());
        }
        // Image(gm::Canvas* _canvas)
        // : gm::GUI(_canvas) {
        //     subclass_name = "IMAGE";
        // }
        Image(gm::GUI* _parent)
        : gm::GUI(_parent) {
            if (node_type_id == 0) {
                node_type_id = 11;
            }
        }
        ~Image() {};
    };

    class Panel : public gm::GUI
    {
    private:
    public:

        sf::RectangleShape rect;

        Panel(gm::GUI* _parent)
        : gm::GUI(_parent) {
            rect.setSize(sf::Vector2f(128,128));
            rect.setFillColor(sf::Color(150, 50, 250));
            rect.setOrigin(rect.getSize().x/2,rect.getSize().y/2);
        
            if (node_type_id == 0) {
                node_type_id = 12;
            }
            
        
        
        };
        ~Panel() {};
        void update() {
            gm::GUI::update();
            rect.setPosition(transform.getPosition().to_sf());
        }
    };
    

}


#endif