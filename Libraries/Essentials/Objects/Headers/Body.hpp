#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <MCGE/Essentials/Objects/Headers/CollisionShape.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>


namespace gm {

class Body : public gm::GameObject
{
private:
public:

    std::vector<gm::CollisionShape> collisions;
    bool is_static = true;
    int body_id;

    Body();
    Body(int _x, int _y);
    ~Body();

    void addShape(gm::CollisionShape _shape);

    void setFillColor(sf::Color _col);

    void start();

    void update();

    bool isColliding(gm::Body _b);
};

}