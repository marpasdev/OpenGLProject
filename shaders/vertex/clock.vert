#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform mat4 hourRot = mat4(1.0);
uniform mat4 minuteRot = mat4(1.0);
uniform mat4 secondRot = mat4(1.0);

out vec3 vertexColor;

void main() {
    vertexColor = normal;

    mat4 handRot = mat4(1.0);

    if (color == vec3(1.0, 0.0, 0.0)) {         // second hand
        vertexColor = vec3(1.0, 0.0, 0.0);   
        handRot = secondRot;
    } else if (color == vec3(0.0, 1.0, 0.0)) {  // minute hand
        vertexColor = vec3(0.0);                
        handRot = minuteRot;
    } else if (color == vec3(0.0, 0.0, 1.0)) {  // hour hand
        vertexColor = vec3(0.0);
        handRot = hourRot;
    } else if (color == vec3(0.0f)) {
        vertexColor = vec3(0.5);       
    } else if (color == vec3(1.0, 1.0, 0.0)) {
        vertexColor = vec3(5.0 / 255.0, 195.0 / 255.0, 222.0 / 255.0);
    } else {
        vertexColor = vec3(1.0);
    }
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * handRot * vec4(pos, 1.0);
}