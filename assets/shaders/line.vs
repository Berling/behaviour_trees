#version 330

in vec2 _position;
in vec3 _color;

out vec3 color_;

uniform mat4 projection;
uniform mat4 view;

void main() {
    color_ = _color;
    gl_Position = projection * view * vec4(_position, 0.f, 1.f);
}
