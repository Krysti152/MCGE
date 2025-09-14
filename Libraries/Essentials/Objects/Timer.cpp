#pragma once

#include <MCGE/Essentials/Objects/Headers/Timer.hpp>
#include <MCGE/Essentials/Functions.hpp>



gm::Timer::Timer() {
    node_type_id = 14;
    gm::GameObject::init();
}
void gm::Timer::init(double _set, float _delta) {
    set_sec = _set;
    delta = _delta;
}
gm::Timer::~Timer() {

}

void gm::Timer::emit_signal(std::string _signal) {
    gm::emit_signal(_signal);   
}

void gm::Timer::start() {
    is_counting = true;
}
void gm::Timer::stop() {
    is_counting = false;
}
void gm::Timer::reset() {
    stop();
    act_sec = 0;
    finished = false;
}
void gm::Timer::update() {
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