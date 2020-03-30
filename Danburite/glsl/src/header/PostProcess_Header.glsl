//? #version 460 core

#ifndef __POST_PROCESS_HEADER__
#define __POST_PROCESS_HEADER__

#extension GL_ARB_bindless_texture : require

// #include "Attachment_Header.glsl"
#include "Constant_Header.glsl"

struct Attachment
{
	sampler2D depth;
	sampler2D stencil;
	sampler2D colors[MAX_NUM_COLOR_ATTACHMENTS];
};

uniform Attachment attachment;

vec4 PostProcess_getPixel(const uint colorAttachmentIdx, const vec2 texCoord)
{
	return texture(attachment.colors[colorAttachmentIdx], texCoord);
}

sampler2D PostProcess_getColorAttachment(const uint idx)
{
	return attachment.colors[idx];
}

#endif