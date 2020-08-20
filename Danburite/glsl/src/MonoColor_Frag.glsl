#version 460 core

#include "header/Material_Header.glsl"
#include "header/TranslucencySwitcher_Frag.glsl"

void main()
{
	TranslucencySwitcher_outColor(material.diffuseColor);
} 