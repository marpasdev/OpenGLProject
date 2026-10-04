#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform vec3 translation;
uniform vec3 scale = vec3(1.0);
uniform vec3 rotation;

out vec3 vertexColor;

void main() {
    vertexColor = color;

    float cx = cos(rotation.x);
    float sx = sin(rotation.x);

    float cy = cos(rotation.y);
    float sy = sin(rotation.y);

    float cz = cos(rotation.z);
    float sz = sin(rotation.z);

    vec3 scaled = pos * scale;
    vec3 rotatedX = vec3(
        scaled.x,
        cx * (scaled.y) - sx * (scaled.z),
        sx * (scaled.y) + cx * (scaled.z)
    );
    vec3 rotatedY = vec3(
        cy * rotatedX.x + sy * rotatedX.z,
        rotatedX.y,
        -sy * rotatedX.x + cy * rotatedX.z
        );
    vec3 rotatedZ = vec3(
        cz * (rotatedY.x) - sz * (rotatedY.y),
        sz * (rotatedY.x) + cz * (rotatedY.y),
        rotatedY.z
    );
    gl_Position = vec4(rotatedZ + translation, 1.0);
}