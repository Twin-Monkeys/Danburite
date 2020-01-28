#version 460 core
layout(early_fragment_tests) in;

#include "header/Phong_Header.glsl"

in VsOut
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
}
fsIn;

out vec4 fragColor;

void main()
{
	fragColor = Phong_calcPhongColor(fsIn.worldPos, normalize(fsIn.worldNormal), fsIn.texCoord, fsIn.color);
} 