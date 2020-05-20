#version 460 core

#define VariableInOut_Vert_exportToFrag_worldPos
#define VariableInOut_Vert_exportToFrag_color
#define VariableInOut_Vert_exportToFrag_worldNormal
#define VariableInOut_Vert_exportToFrag_texCoord
#define VariableInOut_Vert_exportToFrag_TBN
#include "header/VariableInOut_Vert_Header.glsl"

#include "header/ModelCamera_Header.glsl"
#include "header/Material_Header.glsl"
#include "header/Bone_Header.glsl"

void main()
{
	VariableInOut_Vert_exportVariablesToFrag();

	vec3 localPos = VertexAttribute_pos;

	if (Material_isVertexBoneEnabled())
		localPos = (Bone_getBoneMatrix(VertexAttribute_boneIndices, VertexAttribute_boneWeights) * vec4(localPos, 1.f)).xyz;

	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, localPos);
} 