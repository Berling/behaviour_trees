#version 330

in vec2 _position;
in vec2 _texcoord;

out vec2 texcoord_;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    texcoord_ = _texcoord;
    gl_Position = projection * view * model * vec4(_position, 0.f, 1.f);
}
