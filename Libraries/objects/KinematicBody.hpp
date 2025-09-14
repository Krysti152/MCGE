#pragma once

#ifndef KINEMATIC_BODY_HPP
#define KINEMATIC_BODY_HPP

#include <SFML/Graphics.hpp>
#include <MCGE/engine.hpp>

namespace gm {

class KinematicBody : public gm::Body
{
private:
public:

    gm::Vector2 velocity;

    std::vector<bool> colliding = {false,false,false,false};
    // std::vector<gm::Body*> colliding_bodies;
    std::vector<int> colliding_bodies;


    KinematicBody() {
        is_static = false;
        node_type_id = 4;
        init();
        // if (node_type_id == 0) {
        // }
        // this->log("Initialized KinematicBody");
    }

    KinematicBody(int _x, int _y) {
        KinematicBody();
        transform.setPosition(_x,_y);
    }

    ~KinematicBody() {
    }

    void move_and_collide();

    void collide(int _dir) {
        std::vector<std::string> dirs = {"Top", "Right", "Bottom", "Left"};

        // 0 - top
        // 1 - right
        // 2 - bottom
        // 3 - left

        colliding[_dir] = true;

        // std::cout<<"Kolizja na "<<dirs[_dir]<<std::endl;
    }

    void start() {

    }

    void update() {
        gm::Body::update();
        // shape.circle.setPosition(shape.transform.position.x, shape.transform.position.y);
        // shape.rect.setPosition(shape.transform.position.x, shape.transform.position.y);
    }
};

}

#endif