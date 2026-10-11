#version 460 core

in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(0.4, clamp(vertexColor.y, 0.3, 1.0), 0.0, 1.0);
}