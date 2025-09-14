#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <MCGE/objects/GameObject.hpp>

#ifndef SPRITE_HPP
#define SPRITE_HPP

namespace gm {

    class Sprite : public sf::Sprite, public gm::GameObject {
        private:
        public:
            Sprite() {
                subclass_name = "SPRITE";
            }
            ~Sprite() {

            }
    };
}

#endif