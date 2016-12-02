#version 330 core

layout (location = 0) in vec3   pos;
layout (location = 1) in vec2   uv;
layout (location = 2) in vec3   normal;

uniform mat4    projection;
uniform mat4    view;
uniform mat4    model;



void main() {
    frag = vec4(pos, 1.f);
    texCoord = vec2(uv.x, 1.f - uv.y);
    n = normal;
    gl_Position = projection * view * model * vec4(pos, 1.f);
}
