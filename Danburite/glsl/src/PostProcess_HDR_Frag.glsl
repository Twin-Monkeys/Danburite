#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"
#include "header/HDR_Header.glsl"
 
out vec4 fragColor;

void main()
{
	fragColor = vec4(PostProcess_getPixel(0, variableInOut_VertToFrag.texCoord).rgb, 1.f);
	fragColor.rgb = HDR_toneMap(fragColor.rgb);
} 