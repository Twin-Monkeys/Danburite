#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec3 fragColor;

void main()
{
	const sampler2DRect colorAttachment = PostProcess_getRectColorAttachment(0);
	fragColor = (texture(colorAttachment, gl_FragCoord.xy).rgb * Bloom_getBlurKernel(0));

	const uint KERNEL_ITER = ((NUM_BLOOM_BLUR_KERNELS + 1) / 2);
	for(uint i = 1U; i < KERNEL_ITER; i++)
    {
		const float kernel = Bloom_getBlurKernel(i);

        fragColor += (texture(colorAttachment, gl_FragCoord.xy + vec2(0.f, i)).rgb * kernel);
        fragColor += (texture(colorAttachment, gl_FragCoord.xy - vec2(0.f, i)).rgb * kernel);
    }
}