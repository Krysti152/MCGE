#pragma once

#include <string>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>

namespace gm {

    struct TimeStamp {
        double seconds;
    };

    class Timer : public gm::GameObject {
        private:
        public:

            double set_sec;
            double act_sec;

            bool is_counting;

            bool finished = false;

            float delta;

            Timer();
            ~Timer();
            void init(double _set, float _delta);
            void emit_signal(std::string _signal);
            void start();
            void stop();
            void reset();
            void update();
    };
}