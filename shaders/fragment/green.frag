#version 460 core

in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor.x * 0.3, vertexColor.y * 0.8, vertexColor.z * 0.1, 1.0);
}