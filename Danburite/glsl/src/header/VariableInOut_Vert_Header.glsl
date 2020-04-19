//? #version 460 core

/*
	VariableInOut_Vert_export.. 등의 #define 문은 반드시
	본 헤더를 include 하기 전에 정의한다.
*/

#ifndef __VARIABLE_IN_OUT_VERT_HEADER__
#define __VARIABLE_IN_OUT_VERT_HEADER__

#if (															\
	defined(VariableInOut_Vert_exportToFrag_worldPos) ||		\
	defined(VariableInOut_Vert_exportToFrag_color) ||			\
	defined(VariableInOut_Vert_exportToFrag_worldNormal) ||		\
	defined(VariableInOut_Vert_exportToFrag_texCoord) ||		\
	defined(VariableInOut_Vert_exportToFrag_TBN)				\
	)
#include "VertexAttribute_Header.glsl"

#if (															\
	defined(VariableInOut_Vert_exportToFrag_worldPos) ||		\
	defined(VariableInOut_Vert_exportToFrag_worldNormal) ||		\
	defined(VariableInOut_Vert_exportToFrag_TBN)				\
	)
#include "Model_Header.glsl"
#endif

out VariableInOut_VertToFrag
{
	#ifdef VariableInOut_Vert_exportToFrag_worldPos
	vec3 worldPos;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_color
	vec4 color;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_worldNormal
	vec3 worldNormal;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_texCoord
	vec2 texCoord;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_TBN
	mat3 TBN;
	#endif
}
variableInOut_VertToFrag;

#endif

void VariableInOut_Vert_exportVariablesToFrag()
{
	#ifdef VariableInOut_Vert_exportToFrag_worldPos
	variableInOut_VertToFrag.worldPos = Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos);
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_color
	variableInOut_VertToFrag.color = VertexAttribute_color;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_worldNormal
	variableInOut_VertToFrag.worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_normal);
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_texCoord
	variableInOut_VertToFrag.texCoord = VertexAttribute_texCoord;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_TBN
	const vec3 T = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_tangent);
	const vec3 B = cross(variableInOut_VertToFrag.worldNormal, T);

	variableInOut_VertToFrag.TBN = mat3(T, B, variableInOut_VertToFrag.worldNormal);
	#endif
}

#endif