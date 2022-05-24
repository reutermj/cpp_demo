#include "Asteroid.h"
#include <cmath>
#include <utility>

#define NumVerts 48

Asteroid::Asteroid(float x, float y, float vx, float vy, float r) : _x(x), _y(y), _vx(vx), _vy(vy), _r(r) {}



void Asteroid::update(float delta) {
    _x += _vx * delta;
    _y += _vy * delta;
}

float Asteroid::x() {
    return _x;
}

float Asteroid::y() {
    return _y;
}

float Asteroid::r() {
    return _r;
}