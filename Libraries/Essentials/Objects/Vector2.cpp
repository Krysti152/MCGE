#pragma once

#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>

void gm::Vector2::lookAt(Vector2 destination) {
        //6             10
    if (x > destination.x) {
        x = -x - abs(destination.x);//-4
    } else {
        x = -x + destination.x;//4
    }
    if (y > destination.y) {
        y = -y - abs(destination.y);
    } else {
        y = -y + destination.y;
    }
}

void gm::Vector2::normalize() {
    float __len = len(Vector2(x,y));
    x = x/__len;
    y = y/__len;
}

gm::Vector2 gm::Vector2::normalized() {
    float __len = len(Vector2(x,y));
    return Vector2{x/__len, y/__len};
}

float gm::Vector2::len(Vector2 __vec) {
return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
}

// float distanceTo(Vector2 b) {
// return (float) abs(x - b.x) + abs(y - b.y);
// }
float gm::Vector2::distanceTo(Vector2 _b) {
    return (float) std::sqrt(std::pow(x - _b.x, 2) + std::pow(y - _b.y, 2));
}

gm::Vector2 gm::Vector2::multiplyBy(float __val) {
    x,y *= __val;
    return gm::Vector2(x,y);
}


sf::Vector2f gm::Vector2::to_sf() {
    return sf::Vector2f{x,y};
}


gm::Vector2::Vector2() {
    x,y = 0;
}
gm::Vector2::Vector2(int n, int m) {
    x = n;
    y = m;
}
gm::Vector2::Vector2(float n, float m) {
    x = n;
    y = m;
}
gm::Vector2::Vector2(unsigned int n, unsigned int m) {
    x = n;
    y = m;
}
gm::Vector2::Vector2(sf::Vector2f _vec) {
    x = _vec.x;
    y = _vec.y;
}

gm::Vector2::~Vector2() {
}