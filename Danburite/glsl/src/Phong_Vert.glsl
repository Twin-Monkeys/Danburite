#version 460 core

#define VariableInOut_Vert_exportToFrag_worldPos
#define VariableInOut_Vert_exportToFrag_color
#define VariableInOut_Vert_exportToFrag_worldNormal
#define VariableInOut_Vert_exportToFrag_texCoord
#define VariableInOut_Vert_exportToFrag_TBN
#include "header/VariableInOut_Vert_Header.glsl"

#include "header/ModelCamera_Header.glsl"

void main()
{
	VariableInOut_Vert_exportVariablesToFrag();
	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 