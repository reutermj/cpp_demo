#ifndef C___DEMO_BULLETS_H
#define C___DEMO_BULLETS_H

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Bullet.h"
#include "ShaderProgram.h"

class Bullets {
    private:
        std::vector<float> xyCoords;
        std::vector<float> xyVelocity;
        GLuint vbo, vao;
        int vboSize;
        std::shared_ptr<ShaderProgram> program;

    public:
        Bullets(std::shared_ptr<ShaderProgram>);
        void draw();
        void createBullet(float, float, float, float);
        void update(float);
};


#endif //C___DEMO_BULLETS_H
