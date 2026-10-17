#version 460 core

in vec3 color;
in vec3 normal;

out vec4 FragColor;

void main() {
    float shade = 0.3 + 0.7 * abs(normal.y);

    FragColor = vec4(shade * color , 1.0);
}