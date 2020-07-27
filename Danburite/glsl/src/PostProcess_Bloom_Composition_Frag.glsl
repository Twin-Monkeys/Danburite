#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec3 fragColor;

void main()
{
	const sampler2DRect srcTex0 = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect srcTex1 = TextureContainer_getTextureAs2DRect(1);

	 const vec3 originalColor = texture(srcTex0, gl_FragCoord.xy).rgb;
	 const vec3 bloomColor = texture(srcTex1, gl_FragCoord.xy).rgb;

	 fragColor = (originalColor + (bloomColor * Bloom_getEffectStrength()));
} 