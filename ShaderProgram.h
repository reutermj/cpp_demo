#ifndef C___DEMO_SHADERPROGRAM_H
#define C___DEMO_SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>
#include "Matrix.h"

class ShaderProgram {
    private:
        GLuint prog;

    public:
        ShaderProgram(std::string, std::string);
        ~ShaderProgram();

        void uniformMatrix(int, Matrix);
        void bind();
        void unbind();

        //The move constructor allows for the OpenGL shader program handle
        //to be transferred to a new ShaderProgram object without risking
        //free-after-free and use-after-free errors related to the owned
        //OpenGL shader program handle.
        ShaderProgram(ShaderProgram&&);

        //Copy constructor and assignment operator must be deleted to prevent
        //free-after-free and use-after-free errors related to the OpenGL shader
        //program. If a ShaderProgram object can be copied, the handle of the
        //OpenGL shader program would be copied to the new object. This would
        //allow for a free-after-free error when the destructor is called on
        //both objects leading to the OpenGL shader program being deleted twice.
        //It would also allow for use-after-free errors if one of the ShaderProgram
        //objects goes out of scope, deletes the OpenGL shader program in the destructor,
        //and the other ShaderProgram object attempts to use the OpenGL shader program.
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
};

#endif //C___DEMO_SHADERPROGRAM_H
