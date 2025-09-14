
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>
#include <MCGE/Essentials/Objects/Headers/KinematicBody.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>

class COLLISIONS {
    private:
    public:
        static bool doCollide(gm::KinematicBody& b1, gm::StaticBody& b2);
};

namespace gm {

    float calcDelta();
    std::string loadTexture(std::string _name, std::string _path);
    std::string createObject(std::string _type, std::string _name);
    void print(std::string __msg);
    void print(gm::Vector2 __msg);
    float distance(gm::Vector2 a, gm::Vector2 b);
    float vector_len(gm::Vector2 __vec);
    gm::Vector2 normalize(gm::Vector2 __vec);
    void printError(std::string _msg);
    void showTextures();
    void updateVideoMode();
    void setResolution(int _x, int _y);
    void setFullScreen(bool _b);
    void setFrameRate(float _f);
    void loadPrefs();
    void connect(std::string _signal,std::function<void ()> _connected);
    void emit_signal(std::string _signal);
    bool doCollide(gm::KinematicBody b1, gm::StaticBody b2);
}