
#pragma once

#include <MCGE/engine.hpp>

#include <MCGE/objects/Sprite.hpp>
#include <MCGE/objects/Animator.hpp>

#ifndef CREATE_OBJECT_HPP
#define CREATE_OBJECT_HPP


namespace gm {

    std::string createObject(std::string _type, std::string _name = "Default") {

        if (_type == "SPRITE") {
            // RENDER_BUFFER.layers[0].push_back(gm::Sprite{});
            return "Utworzono nowy SPRITE";
        } else if (_type == "ANIMATOR") {
            gm::Animator _new_ob;
            _new_ob.name = _name;
            return "Utworzono nowy ANIMATOR";
        }
    }

}


#endif