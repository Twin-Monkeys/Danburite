#version 460 core

#include "header/Material_Header.glsl"
#include "header/TranslucencySwitcher_Frag_Header.glsl"
#include "header/Camera_Header.glsl"

void main()
{
	const float viewSpaceDepth = Camera_getViewSpaceDepth(gl_FragCoord.z);
	TranslucencySwitcher_outColor(material.diffuseColor, viewSpaceDepth);
} 