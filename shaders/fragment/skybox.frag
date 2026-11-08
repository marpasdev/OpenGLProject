#version 330

out vec4 FragColor;
uniform samplerCube textureUnitID;

in vec3 uvw;

void main () {
     FragColor = texture(textureUnitID, uvw);
}