#version 460 core

#define VariableInOut_Frag_importFromVert_worldPos
#define VariableInOut_Frag_importFromVert_worldNormal
#define VariableInOut_Frag_importFromVert_texCoord
#define VariableInOut_Frag_importFromVert_TBN
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/Material_Header.glsl"
#include "header/Camera_Header.glsl"

out vec4 fragColor;

void main()
{
	const vec3 envReflection = Material_getEnvReflection
	(
		variableInOut_VertToFrag.worldPos,
		normalize(variableInOut_VertToFrag.worldNormal),
		Camera_getPosition(),
		variableInOut_VertToFrag.texCoord
	).rgb;
	
	fragColor = vec4(envReflection, 1.f);
} 