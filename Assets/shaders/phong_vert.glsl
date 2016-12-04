#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out VS_OUT {
    vec3 fragPos;
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view *  model * vec4(pos, 1.0f);
    vs_out.fragPos = vec3(model * vec4(pos, 1.f));
    vs_out.normal = mat3(transpose(inverse(model))) * normal;
}
