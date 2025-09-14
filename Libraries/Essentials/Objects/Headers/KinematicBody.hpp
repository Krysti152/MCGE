#pragma once

#include <vector>
#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>

namespace gm {

class KinematicBody : public gm::Body
{
private:
public:

    gm::Vector2 velocity;

    std::vector<bool> colliding = {false,false,false,false};
    // std::vector<gm::Body*> colliding_bodies;
    std::vector<int> colliding_bodies;


    KinematicBody();

    KinematicBody(int _x, int _y);

    ~KinematicBody();

    void move_and_collide();

    void collide(int _dir);

    void start();

    void update();

    void isColliding(gm::StaticBody _b);

};

}
