#version 330 core
layout (location = 0) in vec2 aPos;
out vec2 screen_pos;

uniform float x;
uniform float y;

void main() {
	screen_pos = vec2(aPos.x - x, aPos.y - y);
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}
