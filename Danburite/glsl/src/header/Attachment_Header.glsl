//? #version 460 core

#ifndef __ATTACHMENT_HEADER__
#define __ATTACHMENT_HEADER__

#include "Constant_Header.glsl"

struct Attachment
{
	uvec2 depth;
	uvec2 stencil;
	uvec2 color0;
	uvec2 color1;
	uvec2 color2;
	uvec2 color3;
	uvec2 color4;
	uvec2 color5;
	uvec2 color6;
	uvec2 color7;
};

layout(binding = BINDING_POINT_ATTACHMENT) uniform UBAttachment
{
	Attachment attachment;
};

#endif