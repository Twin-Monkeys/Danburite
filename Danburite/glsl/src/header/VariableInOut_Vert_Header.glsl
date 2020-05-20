//? #version 460 core

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
#include "Material_Header.glsl"
#include "Bone_Header.glsl"

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
	vec3 localPos = VertexAttribute_pos;

	mat4 boneMat;
	if (Material_isVertexBoneEnabled())
	{
		boneMat = Bone_getBoneMatrix(VertexAttribute_boneIndices, VertexAttribute_boneWeights);
		localPos = (boneMat * vec4(localPos, 1.f)).xyz;
	}
	variableInOut_VertToFrag.worldPos = Model_getWorldPosition(VertexAttribute_modelMat, localPos);
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_color
	variableInOut_VertToFrag.color = VertexAttribute_color;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_worldNormal
	vec3 localNormal = VertexAttribute_normal;

	if (Material_isVertexBoneEnabled())
		localNormal = (transpose(inverse(mat3(boneMat))) * localNormal);

	variableInOut_VertToFrag.worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, localNormal);
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_texCoord
	variableInOut_VertToFrag.texCoord = VertexAttribute_texCoord;
	#endif

	#ifdef VariableInOut_Vert_exportToFrag_TBN
	const vec3 N = variableInOut_VertToFrag.worldNormal;

	/*
		When tangent vectors are calculated on larger meshes that
		Share a considerable amount of vertices,
		The tangent vectors are generally averaged to give nice and smooth results.
		
		A problem with this approach is that the three TBN vectors
		Could end up non-perpendicular, which means the resulting TBN matrix
		Would no longer be orthogonal.
	*/
	const vec3 T = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_tangent);
	const vec3 normalizedT = normalize(T - (dot(N, T) * N));

	const vec3 B = cross(N, normalizedT);

	variableInOut_VertToFrag.TBN = mat3(normalizedT, B, N);
	#endif
}

#endif