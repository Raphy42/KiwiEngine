#version 330 core

out vec4 fragColor;

in VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentLightPos;
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D alphaMap;

void main() {
    vec3 normal = texture(normalMap, fs_in.texCoords).rgb;
    normal = normalize(normal * 2.f - 1.f);

    vec3 visibility = texture(alphaMap, fs_in.texCoords).rgb;

    vec3 color = texture(diffuseMap, fs_in.texCoords).rgb;
    vec3 ambient = 0.2f * color;

    vec3 lightDir = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.f);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.f), 32.f);
    vec3 specular = vec3(0.2f) * spec;
    fragColor = vec4(diffuse + ambient + specular, 1.f);
}