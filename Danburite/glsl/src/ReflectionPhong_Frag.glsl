#version 460 core

#include "header/Phong_Header.glsl"
#include "header/VariableInOut_Frag_Header.glsl"

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
		Material_getEnvReflection(
			variableInOut_VertToFrag.worldPos,
			normalize(variableInOut_VertToFrag.worldNormal),
			Camera_getPosition(),
			variableInOut_VertToFrag.texCoord).rgb, .3f);
} 