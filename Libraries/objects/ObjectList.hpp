#pragma once

#include <MCGE/Libraries.hpp>

#include <MCGE/objects.hpp>

#ifndef OBJECT_LIST_HPP
#define OBJECT_LIST_HPP


namespace gm {

struct ObjectList
    {
        std::vector<gm::Sprite> SPRITES;
        std::string FONTS = "assets/fonts/";
        std::string SOUNDS = "assets/fonts/";
    };

}


#endif