#version 460 core
out vec4 FragColor;

in vec3 textCoord;

uniform samplerCube skybox;

void main () {
    FragColor = texture(skybox, textCoord);
}
