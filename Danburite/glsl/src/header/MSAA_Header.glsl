//? #version 460 core

#ifndef __MSAA_HEADER__
#define __MSAA_HEADER__

#include "Constant_Header.glsl"

struct Attachment
{
	sampler2DMS depth;
	sampler2DMS stencil;
	sampler2DMS colors[MAX_NUM_COLOR_ATTACHMENTS];
};

uniform Attachment attachment;

vec4 MSAA_getPixel(const uint colorAttachmentIdx, const vec2 texCoord, const int samplePointIdx)
{
	ivec2 screenCoord;
	screenCoord.x = int(1600 * texCoord.x);
	screenCoord.y = int(900 * texCoord.y);

	return texelFetch(attachment.colors[colorAttachmentIdx], screenCoord, samplePointIdx);
}

#endif