//? #version 460 core

#ifndef __TRANSLUCENCY_SWITCHER_HEADER__
#define __TRANSLUCENCY_SWITCHER_HEADER__

/*
	opaque	: 일반 rgba
	wboit	: RGBA * weight
*/
layout(location = 0) out vec4 TranslucencySwitcher_out0;

/*
	opaque	: 안쓰임
	wboit	: revealage
*/
layout(location = 1) out float TranslucencySwitcher_out1;

struct TranslucencySwitcher
{
	uint mode;
};

layout(binding = BINDING_POINT_TRANSLUCENCY_SWITCHER) uniform UBTranslucencySwitcher
{
	TranslucencySwitcher translucencySwitcher;
};

void TranslucencySwitcher_outColor_opaque(const vec4 color)
{
	TranslucencySwitcher_out0 = vec4(color.rgb, 1.f);
}

void TranslucencySwitcher_outColor_translucency(const vec4 color)
{
	TranslucencySwitcher_out0 = vec4(1.f, 0.f, 0.f, 1.f);
}

void TranslucencySwitcher_outColor(const vec4 color)
{
	if (translucencySwitcher.mode == TRANSLUCENCY_SWITCHER_MODE_OPAQUE)
		TranslucencySwitcher_outColor_opaque(color);
	
	else if (translucencySwitcher.mode == TRANSLUCENCY_SWITCHER_MODE_TRANSLUCENCY)
		TranslucencySwitcher_outColor_translucency(color);
}

#endif