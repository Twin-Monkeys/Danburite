//? #version 460 core

#ifndef __HDR_HEADER__
#define __HDR_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_HDR) uniform UBHDR
{
	layout(offset = 0) float exposure;
}
hdr;

vec3 HDR_toneMap(const vec3 hdrColor)
{
	return (1.f - exp(-hdrColor * hdr.exposure));
}

#endif