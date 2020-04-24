//? #version 460 core

#ifndef __HDR_HEADER__
#define __HDR_HEADER__

#include "Constant_Header.glsl"

struct HDR
{
	float exposure;
};

layout(binding = BINDING_POINT_HDR) uniform UBHDR
{
	HDR hdr;
};

vec3 HDR_toneMap(const vec3 hdrColor)
{
	return (1.f - exp(-hdrColor * hdr.exposure));
}

#endif