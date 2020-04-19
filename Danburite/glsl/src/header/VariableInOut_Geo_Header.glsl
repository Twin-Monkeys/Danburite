//? #version 460 core

#ifndef __VARIABLE_IN_OUT_GEO_HEADER__
#define __VARIABLE_IN_OUT_GEO_HEADER__

#if (															\
	defined(VariableInOut_Geo_exportToFrag_worldPos)			\
	)

out VariableInOut_GeoToFrag
{
	#ifdef VariableInOut_Geo_exportToFrag_worldPos
	vec3 worldPos;
	#endif
}
variableInOut_GeoToFrag;

#endif

#endif