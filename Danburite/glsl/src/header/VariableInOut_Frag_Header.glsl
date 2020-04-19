//? #version 460 core

#ifndef __VARIABLE_IN_OUT_FRAG_HEADER__
#define __VARIABLE_IN_OUT_FRAG_HEADER__

#if (															\
	defined(VariableInOut_Frag_importFromVert_worldPos) ||		\
	defined(VariableInOut_Frag_importFromVert_color) ||			\
	defined(VariableInOut_Frag_importFromVert_worldNormal) ||	\
	defined(VariableInOut_Frag_importFromVert_texCoord) ||		\
	defined(VariableInOut_Frag_importFromVert_TBN)				\
	)

in VariableInOut_VertToFrag
{
	#ifdef VariableInOut_Frag_importFromVert_worldPos
	vec3 worldPos;
	#endif

	#ifdef VariableInOut_Frag_importFromVert_color
	vec4 color;
	#endif

	#ifdef VariableInOut_Frag_importFromVert_worldNormal
	vec3 worldNormal;
	#endif

	#ifdef VariableInOut_Frag_importFromVert_texCoord
	vec2 texCoord;
	#endif

	#ifdef VariableInOut_Frag_importFromVert_TBN
	mat3 TBN;
	#endif
}
variableInOut_VertToFrag;

#endif

#if (															\
	defined(VariableInOut_Frag_importFromGeo_worldPos)			\
	)

in VariableInOut_GeoToFrag
{
	#ifdef VariableInOut_Frag_importFromGeo_worldPos
	vec3 worldPos;
	#endif
}
variableInOut_GeoToFrag;

#endif

#endif