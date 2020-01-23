#version 460 core

#include "header/Material_Header.glsl"
#include "header/Camera_Header.glsl"

layout(early_fragment_tests) in;

in vec3 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

void main()
{
	Material_setTargetNormal(worldNormal);

	vec3 envRefraction = Material_getEnvRefraction(worldPos, Camera_getPosition()).rgb;
	fragColor = vec4(envRefraction, 1.f);
} 