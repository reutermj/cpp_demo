#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

std::string readFile(std::string path) {
    std::ifstream file(path);
    std::stringstream buf;
    buf << file.rdbuf();
    std::string text = buf.str();
    return text;
}

void compileShader(GLuint shader, const char* text) {
    glShaderSource(shader, 1, &text, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << "Shader compilation failed:" << std::endl << log << std::endl;
    }
}

ShaderProgram::ShaderProgram(std::string vertPath, std::string fragPath) : prog(glCreateProgram()) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    std::string vertText = readFile(std::move(vertPath));
    compileShader(vert, vertText.c_str());

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragText = readFile(std::move(fragPath));
    compileShader(frag, fragText.c_str());

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint success;
    GLchar log[512];
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(prog, 512, nullptr, log);
        std::cout << "Program linking failed:" << std::endl << log << std::endl;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
}

void ShaderProgram::uniformMatrix(int loc, Matrix m) {
    glUniformMatrix3fv(loc, 1, GL_FALSE, m.getData());
}

ShaderProgram::ShaderProgram(ShaderProgram&& source) : prog(source.prog) {
    source.prog = -1;
}

ShaderProgram::~ShaderProgram() {
    if(prog != -1) {
        glDeleteProgram(prog);
        prog = -1;
    } //if prog == -1: this handle was moved to another ShaderProgram object; ignore.
}

void ShaderProgram::bind() {
    glUseProgram(prog);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}