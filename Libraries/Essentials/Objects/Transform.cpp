#pragma once

#include <MCGE/Essentials/Objects/Headers/Transform.hpp>

gm::Transform::Transform() {
    position = gm::Vector2(0,0);
}

gm::Transform::Transform(gm::Vector2 __vec) {
    this->setPosition(__vec);
}
void gm::Transform::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}
void gm::Transform::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void gm::Transform::setPosition(gm::Vector2 vec) {
    this -> position.x = vec.x;
    this -> position.y = vec.y;
}

gm::Vector2 gm::Transform::getPosition() {
    return this->position;
}

void gm::Transform::addPosition(gm::Vector2 __vec) {
    position.x += __vec.x;
    position.y += __vec.y;
}
