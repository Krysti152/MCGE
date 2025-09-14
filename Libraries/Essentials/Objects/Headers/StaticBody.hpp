#pragma once

#include <MCGE/Essentials/Objects/Headers/Body.hpp>

namespace gm {

class StaticBody : public gm::Body
{
private:
public:

    StaticBody();
    StaticBody(int _x, int _y);

    ~StaticBody();

    void start();

    void update();

};

}