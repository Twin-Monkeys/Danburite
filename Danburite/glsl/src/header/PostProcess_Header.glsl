//? #version 460 core

#ifndef __POST_PROCESS_HEADER__
#define __POST_PROCESS_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Attachment_Header.glsl"

vec4 PostProcess_getPixel(const uint colorAttachmentIdx, const vec2 texCoord)
{
	return texture(sampler2D(attachment.colors[colorAttachmentIdx]), texCoord);
}

sampler2D PostProcess_getColorAttachment(const uint idx)
{
	return sampler2D(attachment.colors[idx]);
}

#endif