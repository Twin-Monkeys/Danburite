//? #version 460 core

#ifndef __VARIABLE_IN_OUT_VERT_HEADER__
#define __VARIABLE_IN_OUT_VERT_HEADER__

#if (defined(VariableInOut_Vert_export_worldPos) || defined(VariableInOut_Vert_export_color) || defined(VariableInOut_Vert_export_worldNormal) || defined(VariableInOut_Vert_export_texCoord) || defined(VariableInOut_Vert_export_TBN))
#include "VertexAttribute_Header.glsl"
#endif

#if (defined(VariableInOut_Vert_export_worldPos) || defined(VariableInOut_Vert_export_worldNormal) || defined(VariableInOut_Vert_export_TBN))
#include "Model_Header.glsl"
#endif

out VariableInOut_Vert
{
	#ifdef VariableInOut_Vert_export_worldPos
	vec3 worldPos;
	#endif

	#ifdef VariableInOut_Vert_export_color
	vec4 color;
	#endif

	#ifdef VariableInOut_Vert_export_worldNormal
	vec3 worldNormal;
	#endif

	#ifdef VariableInOut_Vert_export_texCoord
	vec2 texCoord;
	#endif

	#ifdef VariableInOut_Vert_export_TBN
	mat3 TBN;
	#endif
}
variableInOut_Vert;

void VariableInOut_Vert_exportVariables()
{
	#ifdef VariableInOut_Vert_export_worldPos
	variableInOut_Vert.worldPos = Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos);
	#endif

	#ifdef VariableInOut_Vert_export_color
	variableInOut_Vert.color = VertexAttribute_color;
	#endif

	#ifdef VariableInOut_Vert_export_worldNormal
	variableInOut_Vert.worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_normal);
	#endif

	#ifdef VariableInOut_Vert_export_texCoord
	variableInOut_Vert.texCoord = VertexAttribute_texCoord;
	#endif

	#ifdef VariableInOut_Vert_export_TBN
	const vec3 T = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_tangent);
	const vec3 B = cross(variableInOut_Vert.worldNormal, T);

	variableInOut_Vert.TBN = mat3(T, B, variableInOut_Vert.worldNormal);
	#endif
}

#endif