#version 460 core

#define VariableInOut_Vert_export_worldPos
#define VariableInOut_Vert_export_color
#define VariableInOut_Vert_export_worldNormal
#define VariableInOut_Vert_export_texCoord
#define VariableInOut_Vert_export_TBN
#include "header/VariableInOut_Vert_Header.glsl"

#include "header/ModelCamera_Header.glsl"

void main()
{
	VariableInOut_Vert_exportVariables();
	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 