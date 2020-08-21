//? #version 460 core

#ifndef __WBOIT_HEADER__
#define __WBOIT_HEADER__

float Wboit_getWeight(const float viewSpaceDepth, const float alpha)
{
	return (alpha * max(.01f, min(3000.f, 10.f / (1e-5f + pow(viewSpaceDepth / 5.f, 2.f) + pow(viewSpaceDepth / 200.f, 6.f)))));
}

vec4 Wboit_getAccumulation(const vec4 color, const float viewSpaceDepth)
{
	return (color * Wboit_getWeight(viewSpaceDepth, color.a));
}

#endif