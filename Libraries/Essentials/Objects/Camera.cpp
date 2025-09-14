#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <MCGE/Essentials/Objects/Headers/Camera.hpp>

    gm::Camera::Camera() {}

    void gm::Camera::init(int _screen_width, int _screen_height) {
        screen_size = gm::Vector2{_screen_width, _screen_height};
        view.setSize(_screen_width, _screen_height);
        view.setCenter(0,0);
        this->setPosition(0,0);
    }

    gm::Vector2 gm::Camera::getMouseWorldPos() {
        // std::cout<<(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom;
        // std::cout<<(mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom<<std::endl;
        // std::cout<<(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom<<":"<<(mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom<<std::endl;
        return gm::Vector2{(mouse_pos.x - (screen_size.x/2) + transform.position.x * zoom) / zoom, (mouse_pos.y - (screen_size.y/2) + transform.position.y * zoom) / zoom};
        // return gm::Vector2{(mouse_pos.x - (screen_size.x/2/zoom) + transform.position.x * zoom) / zoom, (mouse_pos.y - (screen_size.y/2/zoom) + transform.position.y * zoom) / zoom};
        std::cout<<mouse_pos.x<<":"<<mouse_pos.y<<std::endl;
    }

    bool gm::Camera::focused_window() {
        if (mouse_pos.x > -screen_margin
        && mouse_pos.x < screen_size.x + screen_margin
        && mouse_pos.y > 0
        && mouse_pos.y < screen_size.y + screen_margin) {
            return true;
        }
        return false;
    }
        

        
    void gm::Camera::setPosition(float _x, float _y) {
        transform.setPosition(_x,_y);    
        view.setCenter(_x,_y);
    }
    void gm::Camera::setPosition(gm::Vector2 _vec) {
        setPosition(_vec.x,_vec.y);
    }

    void gm::Camera::move(gm::Vector2 _dir, float _speed) {
        setPosition(transform.position.x + _dir.x * _speed, transform.position.y + _dir.y * _speed);
    }
    void gm::Camera::setZoom(float _f) {
        zoom = _f;
        view.setSize(screen_size.x / zoom, screen_size.y / zoom);
    }

#endif