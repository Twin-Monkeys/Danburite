#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"

layout (location = 0) out vec4 fragColor;

void main()
{
	// Kernel size: 19
	const float kernels[] = float[] (
		0.132572, 0.125472, 0.106373, 0.08078f, 0.05495f, 0.033482f, 0.018275f, 0.008934f, 0.003912f, 0.001535f);

	const sampler2D colorAttachment = PostProcess_getColorAttachment(2);
	vec3 retVal = (texture(colorAttachment, variableInOut_VertToFrag.texCoord).rgb * kernels[0]);

	const float sampleOffset = (1.f / textureSize(colorAttachment, 0).y);

	for(int i = 1; i < 10; ++i)
    {
        retVal += (texture(colorAttachment, variableInOut_VertToFrag.texCoord + vec2(0.f, sampleOffset * i)).rgb * kernels[i]);
        retVal += (texture(colorAttachment, variableInOut_VertToFrag.texCoord - vec2(0.f, sampleOffset * i)).rgb * kernels[i]);
    }

	fragColor = vec4(retVal, 1.f);
}