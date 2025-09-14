#pragma once

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <MCGE/Libraries.hpp>
#include <MCGE/objects/Vector2.hpp>


namespace gm {

class Transform {
    private:
    public:
        Transform();
        Transform(Vector2 vec);

        Vector2 position = {0,0};
        float rotation;
        Vector2 scale = {0,0};
        void setPosition(Vector2 __vec);
        void setPosition(float x, float y);
        void setPosition(int x, int y);
        void addPosition(Vector2 __vec);
        Vector2 getPosition();
};

    Transform::Transform() {
        position = Vector2(0,0);
    }

    Transform::Transform(Vector2 __vec) {
        this->setPosition(__vec);
    }
    void Transform::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    void Transform::setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void Transform::setPosition(Vector2 vec) {
        this -> position.x = vec.x;
        this -> position.y = vec.y;
    }

    Vector2 Transform::getPosition() {
        return this->position;
    }

    void Transform::addPosition(Vector2 __vec) {
        position.x += __vec.x;
        position.y += __vec.y;
    }

}

#endif