#include "Bullets.h"

#include <utility>
#include <iostream>

#define VboInitialSize 20

Bullets::Bullets(std::shared_ptr<ShaderProgram> program) : program(std::move(program)), vboSize(VboInitialSize) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    std::cout << xyCoords.size() << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VboInitialSize, nullptr, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Bullets::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_FLOAT) * xyCoords.size(), xyCoords.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    program->bind();
    program->uniformMatrix(0, Matrix::identity());
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, xyCoords.size() / 2);
    glBindVertexArray(0);
    program->unbind();
}

void Bullets::createBullet(float x, float y, float vx, float vy) {
    xyCoords.push_back(x);
    xyCoords.push_back(y);

    xyVelocity.push_back(vx);
    xyVelocity.push_back(vy);

    if(xyCoords.size() > vboSize) {
        vboSize = vboSize * 2;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vboSize, nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Bullets::update(float delta) {
    for(int i = 0; i < xyCoords.size();) {
        xyCoords[i + 0] += xyVelocity[i + 0] * delta;
        xyCoords[i + 1] += xyVelocity[i + 1] * delta;

        if(xyCoords[i + 0] > 1.0 || xyCoords[i + 0] < -1.0 || xyCoords[i + 1] > 1.0 || xyCoords[i + 1] < -1.0) {
            xyCoords[i + 0] = xyCoords[xyCoords.size() - 2];
            xyCoords[i + 1] = xyCoords[xyCoords.size() - 1];
            xyCoords.pop_back();
            xyCoords.pop_back();

            xyVelocity[i + 0] = xyVelocity[xyVelocity.size() - 2];
            xyVelocity[i + 1] = xyVelocity[xyVelocity.size() - 1];
            xyVelocity.pop_back();
            xyVelocity.pop_back();
        } else {
            i += 2;
        }
    }
}