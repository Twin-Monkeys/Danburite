//? #version 460 core

#ifndef __SKYBOX_HEADER__
#define __SKYBOX_HEADER__

#extension GL_ARB_bindless_texture : require
#include "Constant_Header.glsl"

struct Skybox
{
	uvec2 albedoTex;
	float luminance;
};

layout(binding = BINDING_POINT_SKYBOX) uniform UBSkybox
{
	Skybox skybox;
};

vec4 Skybox_getAlbedo(const vec3 pos)
{
	return (texture(samplerCube(skybox.albedoTex), pos) * skybox.luminance);
}

#endif