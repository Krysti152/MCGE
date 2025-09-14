#pragma once

#include <SFML/Graphics.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>


gm::StaticBody::StaticBody() {
    node_type_id = 5;
    init();
    // this->log("Initialized StaticBody");
}
gm::StaticBody::StaticBody(int _x, int _y) {
    transform.setPosition(_x,_y);
    node_type_id = 5;
    init();
    is_static = true;
    // if (node_type_id == 0) {
    // }
    // shape.transform.setPosition(_x,_y);
    // shape.circle.setPosition(_x,_y);
    // shape.rect.setPosition(_x,_y);
}

gm::StaticBody::~StaticBody() {
}

void gm::StaticBody::start() {

}

void gm::StaticBody::update() {
    gm::Body::update();
}
