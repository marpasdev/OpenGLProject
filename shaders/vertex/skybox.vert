#version 460 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 uvwCoords;

out vec3 uvw;

uniform mat4 viewMatrix=mat4(1.0);
uniform mat4 projectionMatrix=mat4(1.0);

void main()
{
    uvw = uvwCoords;
    uvw = vertexPosition;
    vec4 pos = projectionMatrix * mat4(mat3(viewMatrix)) * vec4(vertexPosition, 1.0);
    gl_Position = pos.xyww;
}