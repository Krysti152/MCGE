#pragma once

#include <SFML/Graphics.hpp>

#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>

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

    Camera();
    void init(int _screen_width, int _screen_height);

    gm::Vector2 getMouseWorldPos();

    bool focused_window();
        

        
    void setPosition(float _x, float _y);
    void setPosition(gm::Vector2 _vec);

    void move(gm::Vector2 _dir, float _speed);
    void setZoom(float _f);
};

}