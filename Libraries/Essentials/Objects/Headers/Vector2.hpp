#pragma once

#include <SFML/System/Vector2.hpp>

namespace gm {

class Vector2
    {
    private:
    public:
        float x;
        float y;

        void lookAt(gm::Vector2 destination);

        void normalize();

        gm::Vector2 normalized();

        float len(gm::Vector2 __vec);

        // float distanceTo(Vector2 b) {
        // return (float) abs(x - b.x) + abs(y - b.y);
        // }
        float distanceTo(gm::Vector2 _b);

        gm::Vector2 multiplyBy(float __val);

        
        sf::Vector2f to_sf();


        Vector2();
        Vector2(int n, int m);
        Vector2(float n, float m);
        Vector2(unsigned int n, unsigned int m);
        Vector2(sf::Vector2f _vec);
        ~Vector2();
};

}
