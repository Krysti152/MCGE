#pragma once

#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include <SFML/Graphics.hpp>
#include <MCGE/engine.hpp>

namespace gm {

class StaticBody : public gm::Body
{
private:
public:

    StaticBody() {
        node_type_id = 5;
        init();
        // this->log("Initialized StaticBody");
    }
    StaticBody(int _x, int _y) {
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

    ~StaticBody() {
    }

    void start() {

    }

    void update() {
        gm::Body::update();
    }

};

}

#endif