//? #version 460 core

#ifndef __GAMMA_CORRECTION_HEADER__
#define __GAMMA_CORRECTION_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_GAMMA_CORRECTION) uniform UBGammaCorrection
{
	layout(offset = 0) float gamma;
}
gammaCorrection;

float GammaCorrection_getGamma()
{
	return gammaCorrection.gamma;
}

#endif