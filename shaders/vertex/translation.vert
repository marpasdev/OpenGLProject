#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

void main() {
    vertexColor = color;
    gl_Position = vec4((cos(90) * pos.x + sin(90) * pos.z) * 0.2, (pos.y - 3) * 0.2, (-sin(90) * pos.x + cos(90) * pos.z) * 0.2, 1.0f);
}