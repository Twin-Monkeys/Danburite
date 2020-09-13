#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec3 fragColor;

void main()
{
	const sampler2DRect srcTex = TextureContainer_getTextureAs2DRect(0);
	fragColor = (texelFetch(srcTex, ivec2(gl_FragCoord.xy)).rgb * Bloom_getBlurKernel(0));

	const uint KERNEL_ITER = ((NUM_BLOOM_BLUR_KERNELS + 1) / 2);
	for(uint i = 1U; i < KERNEL_ITER; i++)
    {
		const float kernel = Bloom_getBlurKernel(i);

        fragColor += (texelFetch(srcTex, ivec2(gl_FragCoord.xy) + ivec2(i, 0)).rgb * kernel);
        fragColor += (texelFetch(srcTex, ivec2(gl_FragCoord.xy) - ivec2(i, 0)).rgb * kernel);
    }
}