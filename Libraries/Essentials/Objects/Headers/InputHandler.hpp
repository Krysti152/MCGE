#pragma once

#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>
#include <MCGE/Libraries.hpp>

#include <SFML/Window.hpp>

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

            void update();

            // Get Normalized dir vector
            gm::Vector2 getNormDir();
            
            // Get raw dir vector
            gm::Vector2 getDir();

            // Get Axis by _name
            float getAxis(std::string _name);

            // Add new axis with _name
            void addNewAxis(std::string _name); 

            // Maps Key to axis Name
            void setButtonMapping(std::string _name, sf::Keyboard::Key _key);
            // Maps Mouse Button to axis Name
            void setButtonMapping(std::string _name, sf::Mouse::Button _btn);
            InputHandler();
            // Loads default mapping configuration
            void loadDefault();
            bool isKeyJustPressed(std::string _name);
            bool isKeyJustUnpressed(std::string _name);
    };

}