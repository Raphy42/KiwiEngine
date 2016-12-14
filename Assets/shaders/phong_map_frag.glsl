#version 330 core

//Adapted from
//  https://github.com/stackgl/glsl-lighting-walkthrough

struct Light {
  vec3 position;
  vec3 color;
  vec3 ambient;
  float falloff;
  float radius;
};

in vec2 v_uv;
in vec3 v_viewPos;
in vec3 v_normal;

const vec2 UV_SCALE = vec2(1.0, 1.0);
const float specularScale = 0.65;
const float shininess = 20.0;
const float roughness = 1.0;
const float albedo = 0.95;

uniform sampler2D texDiffuse;
uniform sampler2D texNormal;
uniform sampler2D texSpecular;
uniform sampler2D texAlpha;

uniform samplerCube depthMap;

uniform float far_plane;
uniform bool shadows;

vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
   vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
   vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
   vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

//uniform int flatShading;
uniform mat4 model;
uniform mat4 view;

uniform Light light;

out vec4 color;

// by Tom Madams
// Simple:
// https://imdoingitwrong.wordpress.com/2011/01/31/light-attenuation/
//
// Improved
// https://imdoingitwrong.wordpress.com/2011/02/10/improved-light-attenuation/
//float attenuation(float r, float f, float d) {
//  float denom = d / r + 1.0;
//  float attenuation = 1.0 / (denom*denom);
//  float t = (attenuation - f) / (1.0 - f);
//  return max(t, 0.0);
//}

// by David Reid - Source:
// https://kookaburragamer.wordpress.com/2013/03/24/user-friendly-exponential-light-attenuation/
float attenuation(float r, float f, float d) {
  return pow(max(0.0, 1.0 - (d / r)), f + 1.0);
}

//http://www.thetenthplanet.de/archives/1180
mat3 cotangent(vec3 N, vec3 p, vec2 uv) {
  // get edge vectors of the pixel triangle
  vec3 dp1 = dFdx(p);
  vec3 dp2 = dFdy(p);
  vec2 duv1 = dFdx(uv);
  vec2 duv2 = dFdy(uv);

  // solve the linear system
  vec3 dp2perp = cross(dp2, N);
  vec3 dp1perp = cross(N, dp1);
  vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
  vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

  // construct a scale-invariant frame
  float invmax = 1.0 / sqrt(max(dot(T,T), dot(B,B)));
  return mat3(T * invmax, B * invmax, N);
}

//stackgl/glsl-perturb-normal
vec3 perturb(vec3 map, vec3 N, vec3 V, vec2 texcoord) {
  mat3 TBN = cotangent(N, -V, texcoord);
  return normalize(TBN * map);
}

#define PI 3.14159265
//glsl-diffuse-oren-nayar/index.glsl
float orenNayarDiffuse(
  vec3 lightDirection,
  vec3 viewDirection,
  vec3 surfaceNormal,
  float roughness,
  float albedo) {

  float LdotV = dot(lightDirection, viewDirection);
  float NdotL = dot(lightDirection, surfaceNormal);
  float NdotV = dot(surfaceNormal, viewDirection);

  float s = LdotV - NdotL * NdotV;
  float t = mix(1.0, max(NdotL, NdotV), step(0.0, s));

  float sigma2 = roughness * roughness;
  float A = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
  float B = 0.45 * sigma2 / (sigma2 + 0.09);

  return albedo * max(0.0, NdotL) * (A + B * s / t) / PI;
}

//glsl-specular-phong/index.glsl
float phongSpecular(
  vec3 lightDirection,
  vec3 viewDirection,
  vec3 surfaceNormal,
  float shininess) {

  //Calculate Phong power
  vec3 R = -reflect(lightDirection, surfaceNormal);
  return pow(max(0.0, dot(viewDirection, R)), shininess);
}

void main() {
    if (texture(texAlpha, v_uv).a < 1.f) //replace alpha by diffuse if alpha undefined
        discard;
    vec3 normal = v_normal;
    vec4 lightPosition = view * vec4(light.position, 1.0);
    vec3 lightVector = lightPosition.xyz - v_viewPos;

    float lightDistance = length(lightVector);
    float falloff = attenuation(light.radius, light.falloff, lightDistance);

    vec2 uv = v_uv * UV_SCALE;
    vec3 diffuseColor = texture(texDiffuse, uv).rgb;
    vec3 normalMap = texture(texNormal, uv).rgb * 2.f - 1.f;
    float specularStrength = texture(texSpecular, uv).r;

    vec3 L = normalize(lightVector);
    vec3 V = normalize(v_viewPos);
    vec3 N = perturb(normalMap, normal, -V, v_uv);

    float specular = specularStrength * phongSpecular(L, V, N, shininess) * specularScale * falloff;
    vec3 diffuse = light.color * orenNayarDiffuse(L, V, N, roughness, albedo) * falloff;
    vec3 ambient = light.ambient;

    color.rgb = diffuseColor * (diffuse + ambient) + specular;
}
