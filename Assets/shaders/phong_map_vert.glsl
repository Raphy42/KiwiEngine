#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 v_normal;
out vec2 v_uv;
out vec3 v_viewPos;

void main() {
     gl_Position = projection * view * model * vec4(pos, 1.f);
     v_uv = uv;
     mat4 modelViewMatrix = view * model;
     vec4 viewModelPosition = modelViewMatrix * vec4(pos, 1.f);
     v_viewPos = viewModelPosition.xyz;
     v_normal = normalize(transpose(inverse(mat3(view * model))) * normal);
}
