#ifndef C___DEMO_MATRIX_H
#define C___DEMO_MATRIX_H

#include <GL/glew.h>

class Matrix {
    private:
        GLfloat arr[9];

    public:
        Matrix(GLfloat[]);
        const GLfloat* getData();
        static Matrix identity();
        static Matrix rotation(float);
        static Matrix scale(float, float);
        static Matrix translation(float, float);

        Matrix operator*(const Matrix&);

        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);
};

#endif //C___DEMO_MATRIX_H
