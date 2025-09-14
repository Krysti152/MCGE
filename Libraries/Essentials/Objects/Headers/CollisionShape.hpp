#pragma once

#include <SFML/Graphics.hpp>
#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>

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


    void init();

    CollisionShape(bool _is_circle);
    CollisionShape(int _radius);
    CollisionShape(gm::Vector2 size);
    ~CollisionShape();

    void setFillColor(sf::Color _col);

    void start();

    void update();

    void setRadius(int _val);

    void setSize(int _x, int _y);
    void setSize(gm::Vector2 _size);

    void setShape(bool _is_circle);
};

}
