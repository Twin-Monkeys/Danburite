//? #version 460 core

#ifndef __GAMMA_CORRECTION_HEADER__
#define __GAMMA_CORRECTION_HEADER__

#include "Constant_Header.glsl"

struct GammaCorrection
{
	float gamma;
};

layout(binding = BINDING_POINT_GAMMA_CORRECTION) uniform UBGammaCorrection
{
	GammaCorrection gammaCorrection;
};

float GammaCorrection_getGamma()
{
	return gammaCorrection.gamma;
}

#endif