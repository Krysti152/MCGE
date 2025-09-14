#pragma once

#ifndef INPUT_HPP
#define INPUT_HPP

#include <MCGE/objects/Vector2.hpp>
#include <MCGE/objects/GameObject.hpp>
#include <MCGE/Libraries.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace gm {

// Input Handler Class
class InputHandler : public gm::GameObject {
        private:
            gm::Vector2 dir = {0,0};
            std::map<std::string, float> Axis = {
                        {"Horizontal", 0},
                        {"Vertical", 0},
                        {"MouseLeft", 0},
                        {"MouseMiddle", 0},
                        {"MouseRight", 0}
                    };
            std::map<std::string, float> prev_Axis;

            std::map<std::string,sf::Keyboard::Key> keys;

            std::map<std::string, sf::Mouse::Button> mouse = {
                {"MouseLeft", sf::Mouse::Left},
                {"MouseMiddle", sf::Mouse::Middle},
                {"MouseRight", sf::Mouse::Right}
            };
        public:

            void update() {

                // Updates dir vector
                int left = 0;
                int right = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    left = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    right = 1;
                };

                int up = 0;
                int down = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    up = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    down = 1;
                };

                prev_Axis = Axis;

                for (const auto &[_name, _key]: prev_Axis) {
                    prev_Axis[_name] = getAxis(_name);
                }

                for ( const auto &[_name, _key]: keys ) {
                    Axis[_name] = sf::Keyboard::isKeyPressed(_key);
                }

                for (const auto &[_name, _btn]: mouse) {
                    Axis[_name] = sf::Mouse::isButtonPressed(_btn);
                }
                

                Axis["Horizontal"] = right - left;
                Axis["Vertical"] = down - up;
                // Axis["Jump"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
                // Axis["Crouch"] = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
                // Axis["Sprint"] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
                // Axis["Action"] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
                // Axis["MouseLeft"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
                // Axis["MouseMiddle"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
                // Axis["MouseRight"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
            }

            // Get Normalized dir vector
            gm::Vector2 getNormDir() {
                return dir.normalized();
            }
            
            // Get raw dir vector
            gm::Vector2 getDir() {
                dir = {getAxis("Horizontal"), getAxis("Vertical")};
                return dir;
            }

            // Get Axis by _name
            float getAxis(std::string _name) {
                return Axis[_name];
            }

            // Add new axis with _name
            void addNewAxis(std::string _name) {
                prev_Axis[_name] = 0;
                Axis[_name] = 0;
                this->log("Added new Axis (" + _name + ")");
            }

            // Maps Key to axis Name
            void setButtonMapping(std::string _name, sf::Keyboard::Key _key) {
                keys[_name] = _key;
                addNewAxis(_name);
            }
            // Maps Mouse Button to axis Name
            void setButtonMapping(std::string _name, sf::Mouse::Button _btn) {
                mouse[_name] = _btn;
                addNewAxis(_name);

            }
            InputHandler() {
                if (node_type_id == 0) {
                    node_type_id = 13;
                }
            }
            // Loads default mapping configuration
            void loadDefault() {
                this->log("Loading Default Button mapping...");
                setButtonMapping("Jump", sf::Keyboard::Space);
                setButtonMapping("Action", sf::Keyboard::E);
                setButtonMapping("Crouch", sf::Keyboard::LControl);
                
                this->log("Finished adding Button mapping");

            }
            bool isKeyJustPressed(std::string _name) {
                return prev_Axis[_name] == 0 && getAxis(_name) != 0;
            }
            bool isKeyJustUnpressed(std::string _name) {
                return prev_Axis[_name] == 1 && getAxis(_name) != 1;
            }
            // 
    };

}

#endif