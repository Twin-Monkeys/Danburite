#version 460 core

#include "header/FXAA_Header.glsl"
#include "header/TextureContainer_Header.glsl"
 
out vec3 fragColor;

void main()
{
	const sampler2DRect srcTex = TextureContainer_getTextureAs2DRect(0);

	const float luminances[9] =
	{
		// origin (0)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy)),


		// crossing neighbors

		// north (1)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(0, 1)),

		// south (2)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(0, -1)),

		// east (3)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(1, 0)),

		// west (4)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(-1, 0)),


		// diagonal neighbors

		// north east (5)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(1, 1)),

		// south east (6)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(1, -1)),

		// north west (7)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(-1, 1)),

		// south west (8)
		FXAA_fetchLuminance(srcTex, ivec2(gl_FragCoord.xy) + ivec2(-1, -1))
	};

	float minLuminance;
	float maxLuminance;
	FXAA_getMinMaxLuminance(luminances, minLuminance, maxLuminance);

	const float contrast = (maxLuminance - minLuminance);
	const float contrastThreshold = FXAA_getContrastThreshold(maxLuminance);

	const vec3 originalColor = texelFetch(srcTex, ivec2(gl_FragCoord.xy)).rgb;

	if (contrast < contrastThreshold)
	{
		fragColor = originalColor;
		return;
	}

	const FXAA_BlendingMeta blendingMeta = FXAA_getBlendingMeta(luminances);

	const float pixelBlendingFactor = FXAA_getPixelBlendingFactor(luminances, contrast);
	const float edgeBlendingFactor = FXAA_getEdgeBlendingFactor(srcTex, blendingMeta, gl_FragCoord.xy);
	const float finalBlendingFactor = max(pixelBlendingFactor, edgeBlendingFactor);

	const vec2 offset = (blendingMeta.normal * finalBlendingFactor);
	fragColor = texture(srcTex, gl_FragCoord.xy + offset).rgb;
}