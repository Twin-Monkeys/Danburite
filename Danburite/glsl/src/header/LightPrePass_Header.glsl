//? #version 460 core

#ifndef __LIGHT_PREPASS_HEADER__
#define __LIGHT_PREPASS_HEADER__

#include "Constant_Header.glsl"

struct LightPrePass
{
	uint currentLightIdx;
};

layout(binding = BINDING_POINT_LIGHT_PREPASS) uniform UBLightPrePass
{
	LightPrePass lightPrePass;
};

uint LightPrePass_getCurrentLightIdx()
{
	return lightPrePass.currentLightIdx;
}

#endif