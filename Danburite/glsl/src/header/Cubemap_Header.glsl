//? #version 460 core

#ifndef __CUBEMAP_HEADER__
#define __CUBEMAP_HEADER__

struct Cubemap
{
	samplerCube albedoTex;
};

uniform Cubemap cubemap;

vec4 Cubemap_getAlbedo(const vec3 pos)
{
	return texture(cubemap.albedoTex, pos);
}

#endif