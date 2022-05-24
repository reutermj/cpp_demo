#include "Ship.h"

#include <utility>
#include "Matrix.h"
#include <cmath>

void Ship::draw() {
    auto ident = Matrix::scale(0.25 * 600/800.0, 0.25);
    auto rot = Matrix::rotation(r);
    auto trans = Matrix::translation(x, y);
    auto bla = trans * ident * rot;
    program->bind();
    program->uniformMatrix(0, bla);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    program->unbind();

    bullets.draw();
}

Ship::Ship(std::shared_ptr<ShaderProgram> program) : program(program), x(0), y(0), velocity(0), r(0), rr(0), bullets(Bullets(program)){
    GLfloat vertices[] = {
            -0.75f, -1.0f,
            0.0f, 1.0f,
            0.75f, -1.0f,
            0.0f, 0.0f
    };

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

void Ship::setForwardVelocity(float v) {
    velocity = v;
}

void Ship::setRotationRate(float rate) {
    rr = rate;
}

void Ship::update(float delta, bool shouldFire) {
    bullets.update(delta);

    r += rr * delta;
    float c = std::cos(r + M_PI / 2);
    float s = std::sin(r + M_PI / 2);
    x += c * delta * velocity;
    y += s * delta * velocity;

    if(shouldFire) bullets.createBullet(x + c * 0.25 * 600/800.0, y + s * .25, c, s);
}

Ship::~Ship() {
    if(vbo != -1) {
        glDeleteBuffers(1, &vbo);
        vbo = -1;
    }
    if(vao != -1) {
        glDeleteVertexArrays(1, &vao);
        vao = -1;
    }
}