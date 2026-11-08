#version 460 core

in vec4 worldPos;
in vec3 worldNor;
in vec3 worldColor;

uniform vec3 cameraPos;

out vec4 fragColor;

// float attenuation(float dist, float constant, float linear, float quadratic) {
//     return clamp(1 / (const + linear * dist + quadratic * dist * dist), 0.0, 1.0);
// }

void main() {


    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPosition - worldPos.xyz);

    // float distVec = cameraPos - lightPosition;
    // float dist = sqrt(distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z);
    // float att = attenuation(dist, 1.0, 0.09, 0.032);

    float diff = max(dot(normalize(lightDir), normalize(worldNor)), 0.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(worldNor));

    vec3 viewDir = normalize(cameraPos - worldPos.xyz);

    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    }

    vec4 objectColor = vec4(worldColor, 1.0);

    fragColor = ambient * objectColor + (diff * objectColor) + spec * vec4(1.0, 1.0, 1.0, 1.0);
}