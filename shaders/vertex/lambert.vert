#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nor;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 worldPos;
out vec3 worldNor;

void main() {

    worldPos = vec3(modelMatrix * vec4(pos, 1.0f));
    worldNor = nor;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}