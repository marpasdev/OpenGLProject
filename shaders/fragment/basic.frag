#version 460 core

in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(abs(vertexColor.x), abs(vertexColor.y), abs(vertexColor.z), 1.0);
}