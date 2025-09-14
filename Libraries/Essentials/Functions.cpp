
#pragma once

#include <MCGE/Essentials/Variables.hpp>
#include <MCGE/Essentials/Functions.hpp>


#include <MCGE/Essentials/Objects/Headers/KinematicBody.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>


bool COLLISIONS::doCollide(gm::KinematicBody& b1, gm::StaticBody& b2) {
        // for (const auto& bod : STATIC_BODIES) {
        //     std::cout<<bod->name<<std::endl;
        // }
        std::cout<<"Collides!"<<std::endl;
        return false;
};

namespace gm {


    float calcDelta() {
        DELTA = 1000000 / FRAME_RATE;
        return DELTA / 1000000;
    }
    
    std::string loadTexture(std::string _name, std::string _path) {
        sf::Texture _new_texture;
        if (!_new_texture.loadFromFile(_path)) {
            return "Nie załadowano " + _name + "(" + _path + ")";
        }
        TEXTURES[_name] = _new_texture;
        return "Załadowano pomyślnie " + _name + "(" + _path + ")";
    }

    std::string createObject(std::string _type, std::string _name = "Default") {

        if (_type == "SPRITE") {
            // RENDER_BUFFER.layers[0].push_back(gm::Sprite{});
            return "Utworzono nowy SPRITE";
        } else if (_type == "ANIMATOR") {
            gm::Animator _new_ob;
            _new_ob.name = _name;
            return "Utworzono nowy ANIMATOR";
        }
    }

    void print(std::string __msg) {
        std::cout<<__msg<<std::endl;
    }

    void print(gm::Vector2 __msg) {
        for (int i = 0; i<2; i++) {
            std::cout<<'['<<__msg.x<<", "<<__msg.y<<']'<<std::endl;
        }
    }

    float distance(gm::Vector2 a, gm::Vector2 b) {
        return (float) abs(a.x - b.x) + abs(a.y - b.y);
    }


    float vector_len(gm::Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
    }

    gm::Vector2 normalize(gm::Vector2 __vec) {

        return gm::Vector2(__vec.x/vector_len(__vec), __vec.y/vector_len(__vec));
        
    }


    void printError(std::string _msg) {
        std::cout<<"[ERROR]"<<_msg<<std::endl;
    }

    void showTextures() {
        for (const auto &[name,tex] : TEXTURES) {
            std::cout<<name<<std::endl;
        }
    }

    void updateVideoMode() {
        VIDEO_MODE = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void setResolution(int _x, int _y) {
        SCREEN_WIDTH = _x;
        SCREEN_HEIGHT = _y;

        updateVideoMode();
        if (IS_RUNNING) {
            WINDOW.create(VIDEO_MODE, NAME, IS_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Titlebar);
        }
    }
    void setFullScreen(bool _b) {
        IS_FULLSCREEN = _b;
        if (IS_RUNNING) {
            WINDOW.create(VIDEO_MODE, NAME, IS_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Titlebar);
        }
    }

    void setFrameRate(float _f) {
        if (!IS_RUNNING) {
            FRAME_RATE = _f;
            calcDelta();
        }
    }

    void loadPrefs() {
        std::string line;
        std::ifstream prefs_f("pref.ini");
        std::vector<std::string> settings;
        bool pref_fsc;
        std::string word;
        while (std::getline(prefs_f, line)) {
            if (line.find('[') == std::string::npos) {
                std::stringstream setting(line);
                while (std::getline(setting, word, '=')) {
                    settings.push_back(word);
                }
            }
        }
        for (int i = 1; i < settings.size(); i+=2) {
            std::cout<<settings[i-1]<<':'<<settings[i]<<std::endl;
            if (settings[i-1] == "fullscreen") {
                if (settings[i] == "true") {
                    IS_FULLSCREEN = true;
                }
            }
            if (settings[i-1] == "scr_width") {
                SCREEN_WIDTH =  std::stoi(settings[i]);
            }
            if (settings[i-1] == "scr_height") {
                SCREEN_HEIGHT =  std::stoi(settings[i]);
            }
            if (settings[i-1] == "fps") {
                FRAME_RATE =  std::stoi(settings[i]);
            }
        }
    }

    void connect(std::string _signal,std::function<void ()> _connected) {
        signals[_signal] = _connected;
    }

    void emit_signal(std::string _signal) {
        for (const auto& [signal, func] : signals ) {
            if (signal == _signal) {
                signals[_signal]();
                return;
            }
        }
    }


}