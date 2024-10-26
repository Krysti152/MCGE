#pragma once


#include <MCGE/Libraries.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <MCGE/objects/Sprite.hpp>

#ifndef RENDER_BUFFER_HPP
#define RENDER_BUFFER_HPP

namespace gm {

    class Layer
    {
    private:
    public:
        std::vector<gm::Sprite> sprites;
        
    };

    class RenderBuffer
    {
    private:
    public:

    std::vector<Layer> layers = {gm::Layer{{}}};

    void addLayer(Layer _layer) {
        layers.push_back(_layer);
    }

    void addSprite(gm::Sprite _spr, int _layer = 0) {
        layers[_layer].sprites.push_back(_spr);
    }

    RenderBuffer() {

    }
    ~RenderBuffer() {

    }
    };

}

#endif