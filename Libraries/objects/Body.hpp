#pragma once

#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <MCGE/engine.hpp>
#include <MCGE/objects/Body.hpp>

namespace gm {

class Body : public gm::GameObject
{
private:
public:

    std::vector<CollisionShape> collisions;

    bool is_static = true;
    int body_id;

    Body() {
        // if (node_type_id == 0) {
        node_type_id = 6;
        // }
        // this->log("Initialized Body");
    }
    Body(int _x, int _y) {
        transform.setPosition(_x,_y);
        // if (node_type_id == 0) {
        node_type_id = 6;
        // }
        // this->log("Initialized Body");
        // shape = gm::CollisionShape("RECTANGLE");
        // shape.transform.setPosition(_x,_y);
    }

    ~Body() {
    }

    void addShape(gm::CollisionShape _shape) {
        _shape.parent = this;
        _shape.body = gm::ob_data{node_id, node_type_id};
        collisions.push_back(_shape);
    }

    void setFillColor(sf::Color _col) {
        for (int cid = 0; cid < collisions.size(); cid++) {
            collisions[cid].setFillColor(_col);
            collisions[cid].update();
        }
    }

    void start() {

    }

    void update() {

        for (int i = 0; i < collisions.size(); i++) {
            collisions[i].transform.position.x = transform.position.x + collisions[i].offset.x;
            collisions[i].transform.position.y = transform.position.y + collisions[i].offset.y;
            collisions[i].update();
        }
        // for (const CollisionShape& shape : collisions) {
        //     shape.transform.position.x = transform.position.x + shape.offset.x;
        //     shape.transform.position.y = transform.position.y + shape.offset.y;
        //     // shape.transform.setPosition(transform.position.x + shape.offset.x, transform.position.y + shape.offset.y);
        //     shape.update();
        // }
        // shape.circle.setPosition(shape.transform.position.x, shape.transform.position.y);
        // shape.rect.setPosition(shape.transform.position.x, shape.transform.position.y);
    }
};

}

#endif