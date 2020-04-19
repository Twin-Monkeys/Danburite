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
	vec3 envRefraction = Material_getEnvRefraction(worldPos, normalize(worldNormal), Camera_getPosition(), texCoord).rgb;
	fragColor = vec4(envRefraction, 1.f);
} 