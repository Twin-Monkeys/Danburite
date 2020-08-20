#version 460 core

#define VariableInOut_Frag_importFromVert_worldPos
#define VariableInOut_Frag_importFromVert_color
#define VariableInOut_Frag_importFromVert_worldNormal
#define VariableInOut_Frag_importFromVert_texCoord
#define VariableInOut_Frag_importFromVert_TBN
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/Phong_Header.glsl"
#include "header/TranslucencySwitcher_Frag.glsl"

void main()
{
	/*
		Normalizing normals in the vertex shader and then passing them to the fragment shader
		doesn't ensure they are normalized after being passed.
		By only passing the normals in the vertex shader and then
		normalizing them in the fragment shader the problem (multisample white dot artifact) was fixed.
	*/
	const vec4 outColor =
		Phong_calcPhongColor(
			variableInOut_VertToFrag.worldPos, normalize(variableInOut_VertToFrag.worldNormal),
			variableInOut_VertToFrag.TBN, variableInOut_VertToFrag.texCoord, variableInOut_VertToFrag.color);

	TranslucencySwitcher_outColor(outColor);
} 