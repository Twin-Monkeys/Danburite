
//? #version 460 core

#ifndef __MSAA_HEADER__
#define __MSAA_HEADER__

#extension ARB_bindless_texture: require

#include "Attachment_Header.glsl"

// AMD Bug; Cannot use bindless sampler2DMS

sampler2DMS MSAA_getColorAttachment(const uint idx)
{
	uvec2 handle;

	if (idx == 0)
		handle = attachment.color0;

	else if (idx == 1)
		handle = attachment.color1;

	else if (idx == 2)
		handle = attachment.color2;

	else if (idx == 3)
		handle = attachment.color3;

	else if (idx == 4)
		handle = attachment.color4;

	else if (idx == 5)
		handle = attachment.color5;

	else if (idx == 6)
		handle = attachment.color6;

	else if (idx == 7)
		handle = attachment.color7;

	return sampler2DMS(handle);
}

vec4 MSAA_getPixel(const uint colorAttachmentIdx, const int samplePointIdx)
{
	return texelFetch(MSAA_getColorAttachment(colorAttachmentIdx), ivec2(gl_FragCoord.xy), samplePointIdx);
}

#endif