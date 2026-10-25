#version 460 core

in vec4 worldPos;
in vec3 worldNor;
uniform vec3 cameraPos;

out vec4 fragColor;

void main() {
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPosition - worldPos.xyz);

    float diff = max(dot(normalize(lightDir), normalize(worldNor)), 0.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec3 viewDir = normalize(cameraPos - worldPos.xyz);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec4 objectColor = vec4(0.8, 0.0, 0.0, 1.0);

    vec4 spec = vec4(1.0) * pow(max(dot(halfwayDir, normalize(worldNor)), 0.0), 32);

    fragColor = ambient + (diff * objectColor) + spec;
}