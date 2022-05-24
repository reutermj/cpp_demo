#ifndef C___DEMO_ASTEROIDS_H
#define C___DEMO_ASTEROIDS_H

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "ShaderProgram.h"
#include "Asteroid.h"

class Asteroids {
    private:
        GLuint vbo;
        GLuint vao;
        std::vector<Asteroid> asteroids;
        std::shared_ptr<ShaderProgram> program;

    public:
        explicit Asteroids(std::shared_ptr<ShaderProgram>);
        ~Asteroids();

        void createAsteroid(float, float, float, float);
        void draw();
        void update(float);

        Asteroids(Asteroids&&) noexcept;
        Asteroids(const Asteroids&) = delete;
        Asteroids& operator=(const Asteroids&) = delete;
};


#endif //C___DEMO_ASTEROIDS_H
