//? #version 460 core

#ifndef __VARIABLE_IN_OUT_FRAG_HEADER__
#define __VARIABLE_IN_OUT_FRAG_HEADER__

in VariableInOut_VertToFrag
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
	mat3 TBN;
}
variableInOut_VertToFrag;

#endif