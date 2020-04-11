//? #version 460 core

#ifndef __DEPTH_BAKING_CUBEMAP_HEADER__
#define __DEPTH_BAKING_CUBEMAP_HEADER__

#include "Constant_Header.glsl"

struct DepthBakingCubemap
{
	mat4 projViewMatrices[6];
};

layout(binding = BINDING_POINT_DEPTH_BAKING_CUBEMAP) uniform UBDepthBakingCubemap
{
	DepthBakingCubemap depthBakingCubemap;
};

vec4 DepthBakingCubemap_getNDCPosition(const int cubemapSide, vec3 worldPos)
{
	return (depthBakingCubemap.projViewMatrices[cubemapSide] * vec4(worldPos, 1.f));
}

#endif