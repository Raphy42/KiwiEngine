#version 330 core

layout (location = 0) in vec3   pos;
layout (location = 1) in vec2   uv;
layout (location = 2) in vec3   normal;
layout (location = 3) in vec3   tangent;
layout (location = 4) in vec3   bitangent;

uniform mat4    projection;
uniform mat4    view;
uniform mat4    model;

out VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentLightPos;
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} vs_out;

out vec2     texCoord;
out vec4     frag;
out vec3     n;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.f);
    vs_out.fragPos = vec3(model * vec4(pos, 1.f));
    vs_out.texCoords = uv;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);

    // TBN must form a right handed coord system.
    // Some models have symetric UVs. Check and fix.
    if (dot(cross(N, T), B) < 0.0f)
        T = T * -1.0f;
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.tangentLightPos = TBN * lightPos;
    vs_out.tangentViewPos = TBN * viewPos;
    vs_out.tangentFragPos = TBN * vs_out.fragPos;
}
