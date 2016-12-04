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
      mat4 modelViewMatrix = view * model;
       vec4 viewModelPosition = modelViewMatrix * vec4(pos, 1.f);

       // Pass varyings to fragment shader
       v_viewPos = viewModelPosition.xyz;
       v_uv = uv;
       gl_Position = projection * viewModelPosition;

       // Rotate the object normals by a 3x3 normal matrix.
       // We could also do this CPU-side to avoid doing it per-vertex
       mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
       v_normal = normalize(normalMatrix * normal);
}
