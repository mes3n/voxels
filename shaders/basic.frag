#version 460 core

out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, textCoord);
}
