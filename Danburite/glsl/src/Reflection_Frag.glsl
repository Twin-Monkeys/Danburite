#version 460 core

#include "header/Material_Header.glsl"
#include "header/Camera_Header.glsl"

layout(early_fragment_tests) in;

in vec3 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

void main()
{
	Material_setTargetNormal(normalize(worldNormal));

	vec3 envReflection = Material_getEnvReflection(worldPos, Camera_getPosition()).rgb;
	fragColor = vec4(envReflection, 1.f);
} 