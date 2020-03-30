//? #version 460 core

#ifndef __MSAA_HEADER__
#define __MSAA_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Attachment_Header.glsl"

vec4 MSAA_getPixel(const uint colorAttachmentIdx, const int samplePointIdx)
{
	return texelFetch(
		sampler2DMS(attachment.colors[colorAttachmentIdx]),
		ivec2(gl_FragCoord.xy),
		samplePointIdx);
}

#endif