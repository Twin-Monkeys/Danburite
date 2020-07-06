#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"
 
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 extractedColor;

void main()
{
	fragColor = PostProcess_getPixel(0, variableInOut_VertToFrag.texCoord);
} 