#version 460 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec2 uv;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec4 worldPos;
out vec3 worldNor;
out vec4 lightPos;

void main() {

    worldPos = vec4(modelMatrix * vec4(vertexPosition, 1.0f));
    worldNor = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    uv = vertexUV;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}