#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "Ship.h"
#include "ShaderProgram.h"
#include "Asteroid.h"
#include "Bullets.h"
#include "Asteroids.h"
#include <chrono>
#include <cmath>

const GLuint WIDTH = 800, HEIGHT = 600;

#define NumPoints 4

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Asteroids", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    std::string vertFile = "/home/mark/CLionProjects/c++_demo/resources/Ship.vert";
    std::string fragFile = "/home/mark/CLionProjects/c++_demo/resources/Ship.frag";
    std::shared_ptr<ShaderProgram> program(new ShaderProgram(vertFile, fragFile));

    Ship ship(program);
    Asteroids asteroids(program);
    asteroids.createAsteroid(0.0, 0.0, 0.0, 0.0);
    asteroids.createAsteroid(0.0, 0.3, 0.0, 0.0);
    asteroids.createAsteroid(0.3, 0.0, 0.0, 0.0);
    asteroids.createAsteroid(0.3, 0.3, 0.0, 0.0);

    auto lastTime = std::chrono::high_resolution_clock::now();

    glPointSize(5);

    bool spacePressedAlready = false;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ship.draw();
        asteroids.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ship.setForwardVelocity(0.5);
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ship.setForwardVelocity(-0.5);
        else ship.setForwardVelocity(0.0);

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ship.setRotationRate(M_PI);
        else if(glfwGetKey(window, GLFW_KEY_D)  == GLFW_PRESS) ship.setRotationRate(-M_PI);
        else ship.setRotationRate(0.0);

        bool shouldFire = false;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressedAlready) {
            shouldFire = true;
            spacePressedAlready = true;
        } else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            spacePressedAlready = false;
        }

        auto time = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(time - lastTime).count() / 1000000.0 * 0.001;
        lastTime = time;

        ship.update(delta, shouldFire);
        asteroids.update(delta);
    }
    glfwTerminate();
    return 0;
}

