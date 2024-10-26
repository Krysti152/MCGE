#pragma once

#include <MCGE/objects.hpp>

#ifndef SCENE_HPP
#define SCENE_HPP

namespace gm {

    struct ob_list {
        std::vector<gm::Sprite> SPRITES;
        std::vector<gm::Animator> ANIMATORS;
    };

    class Scene {
        private:
        public:
            std::string name;
            Scene() {

            }
            ~Scene() {

            }

    };
    
}

#endif