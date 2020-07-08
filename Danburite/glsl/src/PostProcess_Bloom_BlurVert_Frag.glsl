#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"

layout (location = 0) out vec4 fragColor;

void main()
{
	fragColor = PostProcess_getPixel(2, variableInOut_VertToFrag.texCoord);
}