#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform vec3 translation;
uniform vec3 scale = vec3(1.0);
uniform vec3 rotation;

out vec3 vertexColor;

void main() {
    vertexColor = color;

    float c = cos(rotation.y);
    float s = sin(rotation.y);

    vec3 scaled = pos * scale;
    vec3 rotated = vec3(
        c * scaled.x + s * scaled.z,
        scaled.y,
        -s * scaled.x + c * scaled.z
        );
    gl_Position = vec4(rotated + translation, 1.0);
}