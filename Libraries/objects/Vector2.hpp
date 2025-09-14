#pragma once

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <MCGE/Libraries.hpp>
#include <SFML/System/Vector2.hpp>

namespace gm {

class Vector2
    {
    private:
    public:
        float x;
        float y;

        void lookAt(Vector2 destination) {
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

        void normalize() {
            float __len = len(Vector2(x,y));
            x = x/__len;
            y = y/__len;
        }

        Vector2 normalized() {
            float __len = len(Vector2(x,y));
            return Vector2{x/__len, y/__len};
        }

        float len(Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
        }

        // float distanceTo(Vector2 b) {
        // return (float) abs(x - b.x) + abs(y - b.y);
        // }
        float distanceTo(Vector2 _b) {
            return (float) std::sqrt(std::pow(x - _b.x, 2) + std::pow(y - _b.y, 2));
        }

        gm::Vector2 multiplyBy(float __val) {
            x,y *= __val;
            return gm::Vector2(x,y);
        }

        
        sf::Vector2f to_sf() {
            return sf::Vector2f{x,y};
        }


        Vector2() {
            x,y = 0;
        }
        Vector2(int n, int m) {
            x = n;
            y = m;
        }
        Vector2(float n, float m) {
            x = n;
            y = m;
        }
        Vector2(unsigned int n, unsigned int m) {
            x = n;
            y = m;
        }
        Vector2(sf::Vector2f _vec) {
            x = _vec.x;
            y = _vec.y;
        }

        ~Vector2() {
        }
};

}

#endif