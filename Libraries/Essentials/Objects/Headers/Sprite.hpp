#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>

namespace gm {

    class Sprite : public sf::Sprite, public gm::GameObject {
        private:
        public:
            Sprite();
            ~Sprite();
    };
}
