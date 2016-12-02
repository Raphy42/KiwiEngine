#version 330 core

in vec2     texCoord;
in vec4     frag;
in vec3     n;

out vec4    colour;

uniform sampler2D tex;

void main() {
    colour = vec4(n, 1.f);
//    colour = texture(texe, texCoord);
}