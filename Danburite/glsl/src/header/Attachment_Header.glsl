//? #version 460 core

#ifndef __ATTACHMENT_HEADER__
#define __ATTACHMENT_HEADER__

#include "Constant_Header.glsl"

struct Attachment
{
	uvec2 depth;
	uvec2 stencil;
	uvec2 colors[MAX_NUM_COLOR_ATTACHMENTS];
};

layout(binding = BINDING_POINT_ATTACHMENT) uniform UBAttachment
{
	Attachment attachment;
};

#endif