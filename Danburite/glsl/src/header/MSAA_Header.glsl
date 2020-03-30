
//? #version 460 core

#ifndef __MSAA_HEADER__
#define __MSAA_HEADER__

#extension ARB_bindless_texture: require

#include "Attachment_Header.glsl"

// AMD Bug; Cannot use bindless sampler2DMS
//#include "Constant_Header.glsl"
//
//struct Attachment
//{
//	sampler2DMS depth;
//	sampler2DMS stencil;
//	sampler2DMS colors[MAX_NUM_COLOR_ATTACHMENTS];
//};
//
//uniform Attachment attachment;

vec4 MSAA_getPixel(const uint colorAttachmentIdx, const int samplePointIdx)
{
	return texelFetch(
		sampler2DMS(attachment.colors[colorAttachmentIdx]), ivec2(gl_FragCoord.xy), samplePointIdx);
}

#endif