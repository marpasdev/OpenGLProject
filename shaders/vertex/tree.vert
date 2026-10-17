#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nor;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float shade = 0.0;

out vec3 color;
out vec3 normal;

void main() {

    normal = nor;
    
    if (gl_VertexID > 36443) {
        color = vec3(0.0, 0.3 + shade, 0.0);
    } else {
        color = vec3(0.5, 0.5, 0.0);
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}