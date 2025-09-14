#pragma once

#include <MCGE/Essentials/Objects/Headers/RenderBuffer.hpp>


void gm::RenderBuffer::addLayer(Layer _layer) {
    layers.push_back(_layer);
}

void gm::RenderBuffer::addSprite(gm::Sprite _spr, int _layer = 0) {
    layers[_layer].sprites.push_back(_spr);
}

gm::RenderBuffer::RenderBuffer() {

}
gm::RenderBuffer::~RenderBuffer() {

}