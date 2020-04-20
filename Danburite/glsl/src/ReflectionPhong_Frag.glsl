#version 460 core

#define VariableInOut_Frag_importFromVert_worldPos
#define VariableInOut_Frag_importFromVert_color
#define VariableInOut_Frag_importFromVert_worldNormal
#define VariableInOut_Frag_importFromVert_texCoord
#define VariableInOut_Frag_importFromVert_TBN
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/Phong_Header.glsl"

out vec4 fragColor;

void main()
{
	const vec3 worldNormal = normalize(variableInOut_VertToFrag.worldNormal);
	const vec3 viewDirection = normalize(variableInOut_VertToFrag.worldPos - Camera_getPosition());

	fragColor = Phong_calcPhongColor(
		variableInOut_VertToFrag.worldPos,
		worldNormal,
		variableInOut_VertToFrag.TBN,
		variableInOut_VertToFrag.texCoord,
		variableInOut_VertToFrag.color);
	
	fragColor.rgb = mix(
		fragColor.rgb,
		Material_getEnvReflection(
			worldNormal,
			viewDirection,
			variableInOut_VertToFrag.texCoord).rgb, .3f);
} 