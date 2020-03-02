//? #version 460 core

#ifndef __CUBEMAP_HEADER__
#define __CUBEMAP_HEADER__

#extension GL_ARB_bindless_texture : require
#include "Constant_Header.glsl"

struct Cubemap
{
	uvec2 albedoTex;
};

layout(binding = BINDING_POINT_CUBEMAP) uniform UBCubemap
{
	Cubemap cubemap;
};

vec4 Cubemap_getAlbedo(const vec3 pos)
{
	return texture(samplerCube(cubemap.albedoTex), pos);
}

#endif