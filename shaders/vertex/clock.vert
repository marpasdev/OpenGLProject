#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 vertexColor;

void main() {
    vertexColor = color;

    if (color == vec4(1.0, 0.0, 0.0, 1.0)) {
        
    } else if (color == vec4(0.0, 1.0, 0.0, 1.0)) {

    } else if (color == vec4(0.0, 0.0, 1.0, 1.0)) {

    } else {

    }
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}