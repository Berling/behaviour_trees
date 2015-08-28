#version 330

in vec2 texcoord_;

out vec4 frag_color;

uniform sampler2D albedo;

void main() {
    frag_color = texture(albedo, texcoord_);
}
