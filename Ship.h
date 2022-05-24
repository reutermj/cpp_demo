#ifndef C___DEMO_SHIP_H
#define C___DEMO_SHIP_H

#include <GL/glew.h>
#include <memory>
#include "ShaderProgram.h"
#include "Bullets.h"

class Ship {
    private:
        GLuint vbo;
        GLuint vao;
        std::shared_ptr<ShaderProgram> program;
        float velocity;
        float r, rr;
        float x, y;
        Bullets bullets;

    public:
        Ship(std::shared_ptr<ShaderProgram>);
        ~Ship();
        void draw();
        void setForwardVelocity(float);
        void setRotationRate(float);
        void update(float, bool);

        //Ship owns its OpenGL resources. Disallow copy constructor and
        //copy assignment to prevent use-after-free and free-after-free
        //errors related to the owned OpenGL objects. Prefer use of
        //shared_ptr to share a Ship instance.
        Ship(const Ship&) = delete;
        Ship& operator=(const Ship&) = delete;
};

#endif //C___DEMO_SHIP_H
