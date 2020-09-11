//? #version 460 core

#ifndef __DEPTH_BAKING_CUBEMAP_HEADER__
#define __DEPTH_BAKING_CUBEMAP_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_DEPTH_BAKING_CUBEMAP) uniform UBDepthBakingCubemap
{
	layout(offset = 0) mat4 projViewMatrices[6];
	layout(offset = 384) vec3 center;
	layout(offset = 400) float zFar;
}
depthBakingCubemap;

vec4 DepthBakingCubemap_getNDCPosition(const int cubemapSide, const vec3 worldPos)
{
	return (depthBakingCubemap.projViewMatrices[cubemapSide] * vec4(worldPos, 1.f));
}

float DepthBakingCubemap_getDepth(const vec3 worldPos)
{
	return (length(worldPos - depthBakingCubemap.center) / depthBakingCubemap.zFar);
}

#endif