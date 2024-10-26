#pragma once

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace gm {

class Vector3 {
    private:
    public:
        float x;
        float y;
        float z;

        Vector3() {
            x,y,z = 0;
        }
        Vector3(int n, int m, int o) {
            x = n;
            y = m;
            z = o;
        }
        Vector3(float n, float m, float o) {
            x = n;
            y = m;
            z = o;
        }
        ~Vector3() {
        }
};

}

#endif