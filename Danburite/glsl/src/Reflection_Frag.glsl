#version 460 core

#include "header/Material_Header.glsl"
#include "header/Camera_Header.glsl"

in vec3 worldPos;
in vec3 worldNormal;
in vec2 texCoord;
in mat3 TBN;

out vec4 fragColor;

void main()
{
	vec3 envReflection = Material_getEnvReflection(worldPos, normalize(worldNormal), Camera_getPosition(), texCoord).rgb;
	fragColor = vec4(envReflection, 1.f);
} 