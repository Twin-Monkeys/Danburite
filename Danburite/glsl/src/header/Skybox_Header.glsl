//? #version 460 core

#ifndef __SKYBOX_HEADER__
#define __SKYBOX_HEADER__

#include "Constant_Header.glsl"

#extension GL_ARB_bindless_texture : require

layout(std140, binding = BINDING_POINT_SKYBOX) uniform UBSkybox
{
	layout(offset = 0) uvec2 albedoTex;
	layout(offset = 16) float luminance;
}
skybox;

vec4 Skybox_getAlbedo(const vec3 pos)
{
	return (texture(samplerCube(skybox.albedoTex), pos) * skybox.luminance);
}

#endif