#version 330

in vec3 color_;

out vec4 frag_color;

void main() {
    frag_color = vec4(color_, 1.f);
}
