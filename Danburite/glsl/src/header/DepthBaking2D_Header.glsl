//? #version 460 core

#ifndef __DEPTH_BAKING_2D_HEADER__
#define __DEPTH_BAKING_2D_HEADER__

#include "Constant_Header.glsl"

struct DepthBaking2D
{
	mat4 projViewMat;
};

layout(binding = BINDING_POINT_DEPTH_BAKING_2D) uniform UBDepthBaking2D
{
	DepthBaking2D depthBaking2D;
};

vec4 DepthBaking2D_getNDCPosition(mat4 modelMat, vec3 localPos)
{
	return (depthBaking2D.projViewMat * modelMat * vec4(localPos, 1.f));
}

#endif