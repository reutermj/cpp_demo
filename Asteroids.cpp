#include "Asteroids.h"

#include <cmath>
#include <utility>

#define NumVerts 48

Asteroids::Asteroids(std::shared_ptr<ShaderProgram> program) : program(std::move(program)) {
    GLfloat vertices[NumVerts * 2];

    for(int i = 0; i < NumVerts; i++) {
        float angle = (float)(2.0 * M_PI) / NumVerts * i;
        vertices[i * 2] = std::cos(angle) * (600.0/800.0);
        vertices[i * 2 + 1] = std::sin(angle);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Asteroids::draw() {
    program->bind();
    glBindVertexArray(vao);

    for(auto asteroid : asteroids) {
        auto scale = Matrix::scale(asteroid.r(), asteroid.r());
        auto trans = Matrix::translation(asteroid.x(), asteroid.y());
        program->uniformMatrix(0, scale * trans);
        glDrawArrays(GL_LINE_LOOP, 0, NumVerts);
    }

    glBindVertexArray(0);
    program->unbind();
}

void Asteroids::createAsteroid(float x, float y, float vx, float vy) {
    asteroids.emplace_back(x, y, vx, vy, 0.1);
}

void Asteroids::update(float delta) {
    for(auto asteroid : asteroids) {
        asteroid.update(delta);
    }
}

Asteroids::Asteroids(Asteroids&& source) noexcept : vbo(source.vbo), vao(source.vao), program(std::move(source.program)) {
    source.vbo = -1;
    source.vao = -1;
}

Asteroids::~Asteroids() {
    if(vbo != -1) {
        glDeleteBuffers(1, &vbo);
        vbo = -1;
    }
    if(vao != -1) {
        glDeleteBuffers(1, &vao);
        vao = -1;
    }
}