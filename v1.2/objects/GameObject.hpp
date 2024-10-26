#pragma once

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <MCGE/Libraries.hpp>
#include <MCGE/objects/Transform.hpp>
#include <MCGE/objects/Component.hpp>

namespace gm {

class GameObject {
        private:
        public:
            std::string name;
            bool is_active;
            std::string tag;
            gm::Transform transform;
            std::string subclass_name;
            gm::GameObject* parent;

            GameObject() {
                this -> name = "Game Object";
                this -> is_active = true;
            }

            GameObject(std::string _name) {
                this -> name = _name;
                this -> is_active = true;
            }

            ~GameObject() {

            }
            void setActive(bool _bool) {
                this -> is_active = _bool;
            }

            void update() {
                // std::cout<<subclass_name<<std::endl;
                if (parent != 0) {
                    transform.setPosition(parent->transform.getPosition());
                }
            }
            std::vector<gm::Component> components;

            void log(std::string _msg) {
                std::cout<<name + " (" + subclass_name + "): " + _msg<<std::endl;
            }
};

}

#endif