#pragma once

// #include <MCGE/Libraries.hpp>
#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>



namespace gm {

class Transform {
    private:
    public:
        Transform();
        Transform(gm::Vector2 vec);

        gm::Vector2 position = {0,0};
        float rotation;
        gm::Vector2 scale = {0,0};
        void setPosition(gm::Vector2 __vec);
        void setPosition(float x, float y);
        void setPosition(int x, int y);
        void addPosition(gm::Vector2 __vec);
        gm::Vector2 getPosition();
};

}
