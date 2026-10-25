#version 460 core

in vec3 worldPos;
in vec3 worldNor;
out vec4 fragColor;

void main() {
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = lightPosition - worldPos;

    float diff = max(dot(normalize(lightDir), normalize(worldNor)), 0.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec4 objectColor = vec4(0.8, 0.0, 0.0, 1.0);
    fragColor = ambient + (diff * objectColor);
}