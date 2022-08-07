#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextPos;
// layout (location = 2) in vec3 aOffset;

out vec2 textCoord;

uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
    textCoord = aTextPos;
}
