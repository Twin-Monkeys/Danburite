#version 460 core

#include "header/Phong_Header.glsl"

layout(early_fragment_tests) in;

in vec3 worldPos;
in vec4 color;
in vec3 worldNormal;
in vec2 texCoord;
in mat3 TBN;

out vec4 fragColor;

void main()
{
	fragColor = Phong_calcPhongColor(worldPos, normalize(worldNormal), TBN, texCoord, color);
	fragColor.rgb = mix(fragColor.rgb, Material_getEnvReflection(worldPos, Camera_getPosition()).rgb, .3f);
} 