//? #version 460 core

#ifndef __FXAA_HEADER__
#define __FXAA_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"
#include "Grayscale_Header.glsl"

layout(std140, binding = BINDING_POINT_FXAA) uniform UBFXAA
{
	layout(offset = 0U) float edgeSteps[FXAA_MAX_NUM_EDGE_STEPS];
	layout(offset = (16U * FXAA_MAX_NUM_EDGE_STEPS)) uint numEdgeSteps;
	layout(offset = (16U * FXAA_MAX_NUM_EDGE_STEPS) + 16U) float absoluteThreshold;
	layout(offset = (16U * FXAA_MAX_NUM_EDGE_STEPS) + 32U) float relativeThreshold;
	layout(offset = (16U * FXAA_MAX_NUM_EDGE_STEPS) + 48U) float subpixelBlendingFactor;
}
fxaa;

const uint
	TEXEL_IDX_ORIGIN		= 0U,
	TEXEL_IDX_NORTH			= 1U,
	TEXEL_IDX_SOUTH			= 2U,
	TEXEL_IDX_EAST			= 3U,
	TEXEL_IDX_WEST			= 4U,
	TEXEL_IDX_NORTH_EAST	= 5U,
	TEXEL_IDX_SOUTH_EAST	= 6U,
	TEXEL_IDX_NORTH_WEST	= 7U,
	TEXEL_IDX_SOUTH_WEST	= 8U;

struct FXAA_BlendingMeta
{
	vec2 normal;
	vec2 tangent;
	float gradient;
	float originalLuminance;
	float edgeLuminance;
};

float FXAA_fetchLuminance(const sampler2DRect srcTex, const ivec2 fragCoord)
{
	const vec3 originalColor = texelFetch(srcTex, fragCoord).rgb;
	return Grayscale_getGrayscaledColor(originalColor);
}

float FXAA_sampleLuminance(const sampler2DRect srcTex, const vec2 fragCoord)
{
	const vec3 originalColor = texture(srcTex, fragCoord).rgb;
	return Grayscale_getGrayscaledColor(originalColor);
}

void FXAA_getMinMaxLuminance(const float luminances[9], out float minLuminance, out float maxLuminance)
{
	minLuminance = luminances[TEXEL_IDX_ORIGIN];
	maxLuminance = luminances[TEXEL_IDX_ORIGIN];

	for (uint i = TEXEL_IDX_NORTH; i <= TEXEL_IDX_WEST; i++)
	{
		minLuminance = min(minLuminance, luminances[i]);
		maxLuminance = max(maxLuminance, luminances[i]);
	}
}

float FXAA_getContrastThreshold(const float maxLuminance)
{
	return max(fxaa.absoluteThreshold, fxaa.relativeThreshold * maxLuminance);
}

FXAA_BlendingMeta FXAA_getBlendingMeta(const float luminances[9])
{
	FXAA_BlendingMeta retVal;
	retVal.originalLuminance = luminances[TEXEL_IDX_ORIGIN];

	const float horizontalFactor =
		((abs(luminances[TEXEL_IDX_NORTH] + luminances[TEXEL_IDX_SOUTH] - (2.f * luminances[TEXEL_IDX_ORIGIN])) * 2) +
		abs(luminances[TEXEL_IDX_NORTH_EAST] + luminances[TEXEL_IDX_SOUTH_EAST] - (2.f * luminances[TEXEL_IDX_EAST])) +
		abs(luminances[TEXEL_IDX_NORTH_WEST] + luminances[TEXEL_IDX_SOUTH_WEST] - (2.f * luminances[TEXEL_IDX_WEST])));
			
	const float verticalFactor =
		((abs(luminances[TEXEL_IDX_EAST] + luminances[TEXEL_IDX_WEST] - (2.f * luminances[TEXEL_IDX_ORIGIN])) * 2) +
		abs(luminances[TEXEL_IDX_NORTH_EAST] + luminances[TEXEL_IDX_NORTH_WEST] - (2.f * luminances[TEXEL_IDX_NORTH])) +
		abs(luminances[TEXEL_IDX_SOUTH_EAST] + luminances[TEXEL_IDX_SOUTH_WEST] - (2.f * luminances[TEXEL_IDX_SOUTH])));

	const bool isHorizontal = (horizontalFactor >= verticalFactor);

	if (isHorizontal)
	{

		const float forwardGradient = abs(luminances[TEXEL_IDX_NORTH] - luminances[TEXEL_IDX_ORIGIN]);
		const float backwardGradient = abs(luminances[TEXEL_IDX_SOUTH] - luminances[TEXEL_IDX_ORIGIN]);

		const bool isForward = (forwardGradient > backwardGradient);

		if (isForward)
		{
			retVal.normal = vec2(0.f, 1.f);
			retVal.gradient = forwardGradient;
			retVal.edgeLuminance = ((luminances[TEXEL_IDX_ORIGIN] + luminances[TEXEL_IDX_NORTH]) * .5f);
		}
		else
		{
			retVal.normal = vec2(0.f, -1.f);
			retVal.gradient = backwardGradient;
			retVal.edgeLuminance = ((luminances[TEXEL_IDX_ORIGIN] + luminances[TEXEL_IDX_SOUTH]) * .5f);
		}

		retVal.tangent = vec2(1.f, 0.f);
	}
	else
	{
		const float forwardGradient = abs(luminances[TEXEL_IDX_EAST] - luminances[TEXEL_IDX_ORIGIN]);
		const float backwardGradient = abs(luminances[TEXEL_IDX_WEST] - luminances[TEXEL_IDX_ORIGIN]);

		const bool isForward = (forwardGradient > backwardGradient);

		if (isForward)
		{
			retVal.normal = vec2(1.f, 0.f);
			retVal.gradient = forwardGradient;
			retVal.edgeLuminance = ((luminances[TEXEL_IDX_ORIGIN] + luminances[TEXEL_IDX_EAST]) * .5f);
		}
		else
		{
			retVal.normal = vec2(-1.f, 0.f);
			retVal.gradient = backwardGradient;
			retVal.edgeLuminance = ((luminances[TEXEL_IDX_ORIGIN] + luminances[TEXEL_IDX_WEST]) * .5f);
		}

		retVal.tangent = vec2(0.f, 1.f);
	}

	return retVal;
}

float FXAA_getPixelBlendingFactor(const float luminances[9], const float contrast)
{
	if (contrast < EPSILON)
		return 0.f;

	float avgLuminance = 0.f;

	for (uint i = TEXEL_IDX_NORTH; i <= TEXEL_IDX_SOUTH_WEST; i++)
		avgLuminance += (luminances[i] * ((i >= TEXEL_IDX_NORTH_EAST) ? 1.f : 2.f));

	avgLuminance /= 12.f;

	const float linearFactor = clamp(abs(luminances[TEXEL_IDX_ORIGIN] - avgLuminance) / contrast, 0.f, 1.f);
	const float smoothFactor = smoothstep(0.f, 1.f, linearFactor);

	return ((smoothFactor * smoothFactor) * fxaa.subpixelBlendingFactor);
}

float FXAA_getEdgeBlendingFactor(const sampler2DRect srcTex, const FXAA_BlendingMeta blendingMeta, const vec2 fragCoord)
{
	const float deltaThreshold = (blendingMeta.gradient * .25f);
	const vec2 startingCoord = (fragCoord + (blendingMeta.normal * .5f));

	// forward search
	float forwardStep = 0.f;
	vec2 forwardCoord = startingCoord;

	for (uint stepIter = 0U; stepIter < fxaa.numEdgeSteps; stepIter++)
	{
		const float edgeStep = fxaa.edgeSteps[stepIter];

		forwardStep += edgeStep;
		forwardCoord += (edgeStep * blendingMeta.tangent);

		const float luminanceDelta = (FXAA_sampleLuminance(srcTex, forwardCoord) - blendingMeta.edgeLuminance);
		if (abs(luminanceDelta) > deltaThreshold)
			break;
	}

	// backward search
	float backwardStep = 0.f;
	vec2 backwardCoord = startingCoord;

	for (uint stepIter = 0U; stepIter < fxaa.numEdgeSteps; stepIter++)
	{
		const float edgeStep = fxaa.edgeSteps[stepIter];

		backwardStep += edgeStep;
		backwardCoord -= (edgeStep * blendingMeta.tangent);

		const float luminanceDelta = (FXAA_sampleLuminance(srcTex, backwardCoord) - blendingMeta.edgeLuminance);
		if (abs(luminanceDelta) > deltaThreshold)
			break;
	}

	const float edgeLength = (forwardStep + backwardStep);
	if (edgeLength < EPSILON)
		return 0.f;

	float shortestStep;

	// shortest direction == forward
	if (forwardStep <= backwardStep)
	{
		shortestStep = forwardStep;
		const float luminanceDelta = (FXAA_sampleLuminance(srcTex, forwardCoord) - blendingMeta.edgeLuminance);
		
		/*
			If the deltas go in opposite directions,
			then we're moving away from the edge and should skip blending,
			by using a blend factor of zero.
			
			This ensures that we only blend pixels on one side of the edge.
		*/
		if ((luminanceDelta >= 0.f) == (blendingMeta.originalLuminance >= blendingMeta.edgeLuminance))
			return 0.f;
	}
	else
	{
		shortestStep = backwardStep;
		const float luminanceDelta = (FXAA_sampleLuminance(srcTex, backwardCoord) - blendingMeta.edgeLuminance);

		if ((luminanceDelta >= 0.f) == (blendingMeta.originalLuminance >= blendingMeta.edgeLuminance))
			return 0.f;
	}

	return (.5f - (shortestStep / edgeLength));
}

#endif