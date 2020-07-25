#version 460 core

#define VariableInOut_Frag_importFromVert_worldPos
#define VariableInOut_Frag_importFromVert_worldNormal
#define VariableInOut_Frag_importFromVert_texCoord
#define VariableInOut_Frag_importFromVert_TBN
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/Material_Header.glsl"
#include "header/Camera_Header.glsl"

out vec4 normal3_shininess1;

void main()
{
	// phong에선 잘 되고 있는데??

	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - variableInOut_VertToFrag.worldPos);

	const vec2 finalTexCoord = Material_getTexCoord(
		variableInOut_VertToFrag.texCoord, viewDir, variableInOut_VertToFrag.TBN);

	const vec3 targetNormal = normalize(variableInOut_VertToFrag.worldNormal);

	const vec3 finalNormal =
		Material_getNormal(finalTexCoord, targetNormal, variableInOut_VertToFrag.TBN);

	const float shininess = Material_getShininess(finalTexCoord);

	normal3_shininess1.xyz = finalNormal;
	normal3_shininess1.w = shininess;
} 