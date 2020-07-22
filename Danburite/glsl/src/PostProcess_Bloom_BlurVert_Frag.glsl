#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec4 fragColor;

void main()
{
	const sampler2DRect colorAttachment = PostProcess_getRectColorAttachment(0);
	vec3 retVal = (texture(colorAttachment, gl_FragCoord.xy).rgb * Bloom_getBlurKernel(0));

	const float sampleOffset = (1.f / textureSize(colorAttachment, 0).y);

	const uint KERNEL_ITER = ((NUM_BLOOM_BLUR_KERNELS + 1) / 2);
	for(uint i = 1U; i < KERNEL_ITER; i++)
    {
		const float kernel = Bloom_getBlurKernel(i);

        retVal += (texture(colorAttachment, gl_FragCoord.xy + vec2(0.f, i)).rgb * kernel);
        retVal += (texture(colorAttachment, gl_FragCoord.xy - vec2(0.f, i)).rgb * kernel);
    }

	fragColor = vec4(retVal, 1.f);
}