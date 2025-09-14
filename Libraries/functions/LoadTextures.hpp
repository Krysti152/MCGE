#pragma once

#include <MCGE/engine.hpp>

#ifndef LOAD_TEXTURES_HPP
#define LOAD_TEXTURES_HPP


namespace gm {

    std::string loadTexture(std::string _name, std::string _path) {
        sf::Texture _new_texture;
        if (!_new_texture.loadFromFile(_path)) {
            return "Nie załadowano " + _name + "(" + _path + ")";
        }
        TEXTURES[_name] = _new_texture;
        return "Załadowano pomyślnie " + _name + "(" + _path + ")";
    }

}


#endif