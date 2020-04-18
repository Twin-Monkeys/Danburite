#version 460 core

#include "header/Phong_Header.glsl"

in VariableInOut_VertToFrag
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
	mat3 TBN;
}
variableInOut_VertToFrag;

out vec4 fragColor;

void main()
{
	fragColor = Phong_calcPhongColor(
		variableInOut_VertToFrag.worldPos,
		normalize(variableInOut_VertToFrag.worldNormal),
		variableInOut_VertToFrag.TBN,
		variableInOut_VertToFrag.texCoord,
		variableInOut_VertToFrag.color);
	
	fragColor.rgb = mix(
		fragColor.rgb,
		Material_getEnvReflection(variableInOut_VertToFrag.worldPos, Camera_getPosition()).rgb, .3f);
} 