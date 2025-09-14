#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

#include <MCGE/objects/Vector2.hpp>
#include <MCGE/objects/GameObject.hpp>
// #include <MCGE/engine.hpp>

namespace gm {

class Background : sf::Sprite {
    private:
    public:
        int z_pos;
};

class Camera {
    private:
    public:
        bool isActive = true;
        sf::View view;
        float zoom = 1;
        gm::Vector2 screen_size;
        int screen_margin = 25;
        sf::Vector2i mouse_pos;
        gm::Transform transform;

        std::vector<Background> parallax;

    Camera() {}

    void init(int _screen_width, int _screen_height) {
        screen_size = gm::Vector2{_screen_width, _screen_height};
        view.setSize(_screen_width, _screen_height);
        view.setCenter(0,0);
        this->setPosition(0,0);
    }

    gm::Vector2 getMouseWorldPos() {
        // std::cout<<(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom;
        // std::cout<<(mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom<<std::endl;
        // std::cout<<(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom<<":"<<(mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom<<std::endl;
        return gm::Vector2{(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom, (mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom};
        // return gm::Vector2{(mouse_pos.x - (screen_size.x/2/zoom) + transform.position.x * zoom) / zoom, (mouse_pos.y - (screen_size.y/2/zoom) + transform.position.y * zoom) / zoom};
        std::cout<<mouse_pos.x<<":"<<mouse_pos.y<<std::endl;
    }

    bool focused_window() {
        if (mouse_pos.x > -screen_margin
        && mouse_pos.x < screen_size.x + screen_margin
        && mouse_pos.y > 0
        && mouse_pos.y < screen_size.y + screen_margin) {
            return true;
        }
        return false;
    }
        

        
    void setPosition(float _x, float _y) {
        transform.setPosition(_x,_y);    
        view.setCenter(_x,_y);
    }
    void setPosition(gm::Vector2 _vec) {
        setPosition(_vec.x,_vec.y);
    }

    void move(gm::Vector2 _dir, float _speed) {
        setPosition(transform.position.x + _dir.x * _speed, transform.position.y + _dir.y * _speed);
    }
    void setZoom(float _f) {
        zoom = _f;
        view.setSize(screen_size.x / zoom, screen_size.y / zoom);
    }
};

}

#endif