#pragma once

#ifndef COLLISION_SHAPE_HPP
#define COLLISION_SHAPE_HPP

#include <SFML/Graphics.hpp>
#include <MCGE/objects/Vector2.hpp>
#include <MCGE/objects/GameObject.hpp>
#include <MCGE/engine.hpp>

namespace gm {

class CollisionShape : public GameObject {
    private:
    public:

        // std::string type;
        gm::Vector2 offset = {0,0};
        
        bool is_circle;
        // is a circle
        // false - rectangle
        // true - circle

        // CIRCLE SHAPE
        sf::CircleShape circle{16};
        // radius of a circle
        int radius = 0;

        // RECTANGLE SHAPE
        sf::RectangleShape rect;
        // size of rectangle
        gm::Vector2 size;

        sf::Color fill_color;

        gm::ob_data body;



    void render();


    void init() {
        node_type_id = 7;
        gm::GameObject::init();
    }

    CollisionShape(bool _is_circle = true) {
        init();
        setShape(_is_circle);
    }
    CollisionShape(int _radius) {
        init();
        is_circle = true;
        setRadius(_radius);

    }
    CollisionShape(gm::Vector2 size) {
        init();
        is_circle = false;
        setSize(size);

    }
    ~CollisionShape() {
    }

    void setFillColor(sf::Color _col) {
        fill_color = _col;
    }

    void start() {
        
    }

    void update() {
        // gm::GameObject::update();
        circle.setFillColor(fill_color);
        rect.setFillColor(fill_color);
        if (is_circle) {
            circle.setPosition(transform.position.x, transform.position.y);
            return;
        }
        rect.setPosition(transform.position.x, transform.position.y);
    }

    void setRadius(int _val) {
        radius = _val;
        circle.setOrigin(radius, radius);
    }

    void setSize(int _x, int _y) {
        size = {_x,_y};
        rect.setSize(sf::Vector2f(size.x, size.y));
    }
    void setSize(gm::Vector2 _size) {
        setSize(_size.x, _size.y);
    }

    void setShape(bool _is_circle) {
        is_circle = _is_circle;
        if (_is_circle) {
            setRadius(16);
            return;
        }
        setSize(20,10);
        // rect.setOrigin(size.x/2,size.y/2);
    }
};

}

#endif