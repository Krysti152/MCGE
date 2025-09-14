#pragma once

#include <MCGE/Essentials/Objects/Headers/CollisionShape.hpp>

void gm::CollisionShape::init() {
    node_type_id = 7;
    gm::GameObject::init();
}

gm::CollisionShape::CollisionShape(bool _is_circle = true) {
    init();
    setShape(_is_circle);
}
gm::CollisionShape::CollisionShape(int _radius) {
    init();
    is_circle = true;
    setRadius(_radius);

}
gm::CollisionShape::CollisionShape(gm::Vector2 size) {
    init();
    is_circle = false;
    setSize(size);

}
gm::CollisionShape::~CollisionShape() {
}

void gm::CollisionShape::setFillColor(sf::Color _col) {
    fill_color = _col;
}

void gm::CollisionShape::start() {
    
}

void gm::CollisionShape::update() {
    // gm::GameObject::update();
    circle.setFillColor(fill_color);
    rect.setFillColor(fill_color);
    if (is_circle) {
        circle.setPosition(transform.position.x, transform.position.y);
        return;
    }
    rect.setPosition(transform.position.x, transform.position.y);
}

void gm::CollisionShape::setRadius(int _val) {
    radius = _val;
    circle.setOrigin(radius, radius);
}

void gm::CollisionShape::setSize(int _x, int _y) {
    size = {_x,_y};
    rect.setSize(sf::Vector2f(size.x, size.y));
}
void gm::CollisionShape::setSize(gm::Vector2 _size) {
    setSize(_size.x, _size.y);
}

void gm::CollisionShape::setShape(bool _is_circle) {
    is_circle = _is_circle;
    if (_is_circle) {
        setRadius(16);
        return;
    }
    setSize(20,10);
    // rect.setOrigin(size.x/2,size.y/2);
}