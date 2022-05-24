#include "Matrix.h"

#include <cmath>

//[0 3 6]
//[1 4 7]
//[2 5 8]

Matrix Matrix::operator*(const Matrix& other) {
    GLfloat out[9] { 0.0 };
    out[0] = arr[0] * other.arr[0] + arr[3] * other.arr[1] + arr[6] * other.arr[2];
    out[1] = arr[1] * other.arr[0] + arr[4] * other.arr[1] + arr[7] * other.arr[2];
    out[2] = arr[2] * other.arr[0] + arr[5] * other.arr[1] + arr[8] * other.arr[2];
    out[3] = arr[0] * other.arr[3] + arr[3] * other.arr[4] + arr[6] * other.arr[5];
    out[4] = arr[1] * other.arr[3] + arr[4] * other.arr[4] + arr[7] * other.arr[5];
    out[5] = arr[2] * other.arr[3] + arr[5] * other.arr[4] + arr[8] * other.arr[5];
    out[6] = arr[0] * other.arr[6] + arr[3] * other.arr[7] + arr[6] * other.arr[8];
    out[7] = arr[1] * other.arr[6] + arr[4] * other.arr[7] + arr[7] * other.arr[8];
    out[8] = arr[2] * other.arr[6] + arr[5] * other.arr[7] + arr[8] * other.arr[8];
    return Matrix(out);
}

Matrix::Matrix(GLfloat in[]) {
    for(int i = 0; i < 9; i++) {
        arr[i] = in[i];
    }
}

Matrix Matrix::identity() {
    GLfloat arr[9] { 0.0 };
    arr[0] = 1;
    arr[4] = 1;
    arr[8] = 1;

    return Matrix(arr);
}

Matrix Matrix::rotation(float angle) {
    auto c = std::cos(angle);
    auto s = std::sin(angle);

    GLfloat arr[9] { 0.0 };
    arr[0] = c;
    arr[1] = s;
    arr[3] = -s;
    arr[4] = c;
    arr[8] = 1;

    return Matrix(arr);
}

Matrix Matrix::scale(float x, float y) {
    GLfloat arr[9] { 0.0 };
    arr[0] = x;
    arr[4] = y;
    arr[8] = 1;

    return Matrix(arr);
}

Matrix Matrix::translation(float x, float y) {
    GLfloat arr[9] { 0.0 };
    arr[0] = 1;
    arr[4] = 1;
    arr[6] = x;
    arr[7] = y;
    arr[8] = 1;

    return Matrix(arr);
}

const GLfloat* Matrix::getData() {
    return arr;
}

Matrix::Matrix(const Matrix& other) {
    for(int i = 0; i < 9; i++) {
        arr[i] = other.arr[i];
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    for(int i = 0; i < 9; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}