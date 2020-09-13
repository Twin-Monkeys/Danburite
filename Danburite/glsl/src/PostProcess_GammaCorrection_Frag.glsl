#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/GammaCorrection_Header.glsl"

out vec3 fragColor;

void main()
{
	const sampler2DRect srcTex = TextureContainer_getTextureAs2DRect(0);

	fragColor = texelFetch(srcTex, ivec2(gl_FragCoord.xy)).rgb;
	fragColor = pow(fragColor, vec3(1.f / GammaCorrection_getGamma()));
} 