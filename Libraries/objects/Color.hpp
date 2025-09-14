#pragma once

#ifndef COLOR_HPP
#define COLOR_HPP

namespace gm {

class Color {
        private:
        public:
            int r;
            int g;
            int b;
            int a;
            Color() {
                r,g,b,a = 1;
            }
            Color(int gray) {
                r,g,b = gray;
                a = 1;
            }
};

}

#endif