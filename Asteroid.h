#ifndef C___DEMO_ASTEROID_H
#define C___DEMO_ASTEROID_H

#include <GL/glew.h>
#include <memory>
#include "ShaderProgram.h"

class Asteroid {
    private:
        float _x, _y;
        float _vx, _vy;
        float _r;

    public:
        Asteroid(float, float, float, float, float);

        void update(float);

        float x();
        float y();
        float r();
};

#endif //C___DEMO_ASTEROID_H
