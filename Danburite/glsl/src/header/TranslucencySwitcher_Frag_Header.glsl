//? #version 460 core

#ifndef __TRANSLUCENCY_SWITCHER_HEADER__
#define __TRANSLUCENCY_SWITCHER_HEADER__

#include "Constant_Header.glsl"
#include "Wboit_Header.glsl"

/*
	opaque	: 일반 rgba
	wboit	: RGBA * weight
*/
layout(location = 0) out vec4 TranslucencySwitcher_out0;

/*
	opaque	: 안쓰임
	wboit	: alpha
*/
layout(location = 1) out float TranslucencySwitcher_out1;

/*
	std140:
	stride is always rounded up to the size of a vec4 (16 bytes)

	std430:
	Structure alignment is the same as the alignment for the biggest structure member,
	where three-component vectors are not rounded up to the size of four-component vectors.
	Each structure will start on this alignment, and its size will be the space needed by its members,
	according to the previous rules, rounded up to a multiple of the structure alignment.
*/
layout(std140, binding = BINDING_POINT_TRANSLUCENCY_SWITCHER) uniform UBTranslucencySwitcher
{
	/*
		It needs std140 or std430
	*/
	layout(offset = 0) uint mode;
}
translucencySwitcher;

void TranslucencySwitcher_outColor_opaque(const vec4 color)
{
	TranslucencySwitcher_out0 = vec4(color.rgb, 1.f);
}

void TranslucencySwitcher_outColor_translucency(const vec4 color, const float viewSpaceDepth)
{
	if (color.a < EPSILON)
		discard;

	TranslucencySwitcher_out0 = Wboit_getAccumulation(color, viewSpaceDepth);
	TranslucencySwitcher_out1 = color.a;
}

void TranslucencySwitcher_outColor(const vec4 color, const float viewSpaceDepth)
{
	if (translucencySwitcher.mode == TRANSLUCENCY_SWITCHER_MODE_OPAQUE)
		TranslucencySwitcher_outColor_opaque(color);
	
	else if (translucencySwitcher.mode == TRANSLUCENCY_SWITCHER_MODE_TRANSLUCENCY)
		TranslucencySwitcher_outColor_translucency(color, viewSpaceDepth);
}

#endif