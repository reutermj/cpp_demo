#version 430 core

layout(location = 0) uniform mat3 mat;

layout(location = 0) in vec2 inPos;

void main() {
    vec3 pos = mat * vec3(inPos, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);
}