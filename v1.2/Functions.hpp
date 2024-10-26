#pragma once

#include <MCGE/engine.hpp>

#include <MCGE/Libraries.hpp>

#include <MCGE/functions/LoadTextures.hpp>
#include <MCGE/functions/CalcDelta.hpp>
#include <MCGE/functions/CreateObject.hpp>

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

namespace gm {


    
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

}

#endif