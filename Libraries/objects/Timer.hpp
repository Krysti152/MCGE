#pragma once

#include <chrono>
#include <functional>
#include <SFML/Graphics/Sprite.hpp>
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

            Timer() {
                node_type_id = 14;
                init();
            }
            Timer(double _set, float _delta) {
                Timer();
                set_sec = _set;
                delta = _delta;
            }
            ~Timer() {

            }

            void emit_signal(std::string _signal);

            void start() {
                is_counting = true;
            }
            void stop() {
                is_counting = false;
            }
            void reset() {
                stop();
                act_sec = 0;
                finished = false;
            }
            void update() {
                if (!is_counting) {
                    return;
                }
                act_sec += delta;
                if (act_sec >= set_sec) {
                    finished = true;
                    emit_signal("TIMER_DELAY_FINISHED");
                    reset();
                }
            }
    };
}