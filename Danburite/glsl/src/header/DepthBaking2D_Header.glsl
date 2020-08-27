//? #version 460 core

#ifndef __DEPTH_BAKING_2D_HEADER__
#define __DEPTH_BAKING_2D_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_DEPTH_BAKING_2D) uniform UBDepthBaking2D
{
	layout(offset = 0) mat4 projViewMat;
}
depthBaking2D;

vec4 DepthBaking2D_getNDCPosition(const mat4 modelMat, const vec3 localPos)
{
	return (depthBaking2D.projViewMat * modelMat * vec4(localPos, 1.f));
}

#endif