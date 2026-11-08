#version 460 core

in vec4 worldPos;
in vec3 worldNor;
uniform vec3 cameraPos;

uniform sampler2D textureUnitID;
in vec2 uv;

out vec4 fragColor;

void main() {
    vec3 lightPosition = vec3(0.0, 1.0, 1.0);
    vec3 lightDir = normalize(lightPosition - worldPos.xyz);

    float diff = max(dot(normalize(lightDir), normalize(worldNor)), 0.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(worldNor));

    vec3 viewDir = normalize(cameraPos - worldPos.xyz);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec4 objectColor = texture(textureUnitID, uv);

    fragColor = ambient * objectColor + (diff * objectColor) + spec * vec4(1.0, 1.0, 1.0, 1.0);
}