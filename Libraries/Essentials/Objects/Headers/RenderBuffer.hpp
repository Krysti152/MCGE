#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <MCGE/Essentials/Objects/Headers/Sprite.hpp>
#include <vector>

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

    void addLayer(Layer _layer);
    void addSprite(gm::Sprite _spr, int _layer);

    RenderBuffer();
    ~RenderBuffer();
    };

}
