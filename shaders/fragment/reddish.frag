#version 460 core

in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, vertexColor.y / 2, vertexColor.z / 2, 1.0);
}