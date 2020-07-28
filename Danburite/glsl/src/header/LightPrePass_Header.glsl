//? #version 460 core

#ifndef __LIGHT_PREPASS_HEADER__
#define __LIGHT_PREPASS_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

struct LightPrePass
{
	uint currentLightIdx;
	uvec2 lightAmbientTex;
	uvec2 lightDiffuseTex;
	uvec2 lightSpecularTex;
};

layout(binding = BINDING_POINT_LIGHT_PREPASS) uniform UBLightPrePass
{
	LightPrePass lightPrePass;
};

uint LightPrePass_getCurrentLightIdx()
{
	return lightPrePass.currentLightIdx;
}

vec3 LightPrePass_getLightAmbient(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.lightAmbientTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightDiffuse(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.lightDiffuseTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightSpecular(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.lightSpecularTex), screenCoord).rgb;
}

#endif