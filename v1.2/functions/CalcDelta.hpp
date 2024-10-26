
#pragma once

#include <MCGE/engine.hpp>

#ifndef CALC_DELTA_HPP
#define CALC_DELTA_HPP


namespace gm {

    float calcDelta() {
        DELTA = 1000000 / FRAME_RATE;
        return DELTA / 1000000;
    }

}


#endif