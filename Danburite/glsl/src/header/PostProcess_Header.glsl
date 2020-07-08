//? #version 460 core

#ifndef __POST_PROCESS_HEADER__
#define __POST_PROCESS_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Attachment_Header.glsl"

sampler2D PostProcess_getColorAttachment(const uint idx)
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

	return sampler2D(handle);
}

vec4 PostProcess_getPixel(const uint colorAttachmentIdx, const vec2 texCoord)
{
	return texture(PostProcess_getColorAttachment(colorAttachmentIdx), texCoord);
}

#endif