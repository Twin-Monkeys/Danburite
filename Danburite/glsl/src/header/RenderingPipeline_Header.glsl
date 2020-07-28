//? #version 460 core

#ifndef __RENDERING_PIPELINE_HEADER__
#define __RENDERING_PIPELINE_HEADER__

#include "Constant_Header.glsl"

struct RenderingPipeline
{
	uint type;
};

layout(binding = BINDING_POINT_RENDERING_PIPELINE) uniform UBRenderingPipeline
{
	RenderingPipeline renderingPipeline;
};

uint RenderingPipeline_getType()
{
	return renderingPipeline.type;
}

#endif