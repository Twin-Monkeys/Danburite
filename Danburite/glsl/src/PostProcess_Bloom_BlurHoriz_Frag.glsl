#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"

layout (location = 1) out vec4 fragColor;

void main()
{
	const sampler2D colorAttachment = PostProcess_getColorAttachment(1);
	vec3 retVal = (texture(colorAttachment, variableInOut_VertToFrag.texCoord).rgb * Bloom_getBlurKernel(0));

	const float sampleOffset = (1.f / textureSize(colorAttachment, 0).x);

	const uint KERNEL_ITER = ((NUM_BLOOM_BLUR_KERNELS + 1) / 2);
	for(uint i = 1U; i < KERNEL_ITER; i++)
    {
		const float kernel = Bloom_getBlurKernel(i);

        retVal += (texture(colorAttachment, variableInOut_VertToFrag.texCoord + vec2(sampleOffset * i, 0.f)).rgb * kernel);
        retVal += (texture(colorAttachment, variableInOut_VertToFrag.texCoord - vec2(sampleOffset * i, 0.f)).rgb * kernel);
    }

	fragColor = vec4(retVal, 1.f);
}