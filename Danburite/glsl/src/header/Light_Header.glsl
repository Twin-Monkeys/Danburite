//? #version 460 core

#ifndef __LIGHT_HEADER__
#define __LIGHT_HEADER__

#include "Constant_Header.glsl"

struct Light
{
	bool enabled;

	// base properties
	uint type;
	vec3 albedo;
	float ambientStrength;
	float diffuseStrength;
	float specularStrength;

	// directional, spot
	vec3 direction;

	// point, spot
	vec3 pos;
	float attConst;
	float attLinear;
	float attQuad;

	// spot
	float innerCutOff;
	float outerCutOff;
};

layout(binding = BINDING_POINT_LIGHT) uniform UBLight
{
	Light light[MAX_NUM_LIGHTS];
};

vec3 Light_targetPos;

void Light_setLightTargetPos(vec3 targetPos)
{
	Light_targetPos = targetPos;
}

bool Light_isLightEnabled(uint lightIndex)
{
	return light[lightIndex].enabled;
}

vec3 Light_getLightDirection(uint lightIndex)
{
	const uint LIGHT_TYPE = light[lightIndex].type;
	vec3 retVal = vec3(0.f);

	if (LIGHT_TYPE == LIGHT_TYPE_DIRECTIONAL)
	{
		retVal = light[lightIndex].direction;
	}
	else if (
		(LIGHT_TYPE == LIGHT_TYPE_POINT) ||
		(LIGHT_TYPE == LIGHT_TYPE_SPOT))
	{
		retVal = normalize(Light_targetPos - light[lightIndex].pos);
	}

	return retVal;
}

float Light_getLightDistance(uint lightIndex)
{
	return length(Light_targetPos - light[lightIndex].pos);
}

float Light_getLightStrength(uint lightIndex)
{
	const uint LIGHT_TYPE = light[lightIndex].type;
	float retVal = 1.f;

	if (LIGHT_TYPE == LIGHT_TYPE_SPOT)
	{
		const float theta = dot(light[lightIndex].direction, Light_getLightDirection(lightIndex));
		
		retVal = clamp(
			(theta - light[lightIndex].outerCutOff) /
			(light[lightIndex].innerCutOff - light[lightIndex].outerCutOff),
			0.f, 1.f);

		const float lightDist = Light_getLightDistance(lightIndex);
		const float attenuation =
			(light[lightIndex].attConst +
			(light[lightIndex].attLinear * lightDist) +
			(light[lightIndex].attQuad * lightDist * lightDist));

		retVal /= attenuation;
	}
	else if (LIGHT_TYPE == LIGHT_TYPE_POINT)
	{
		const float lightDist = Light_getLightDistance(lightIndex);
		const float attenuation =
			(light[lightIndex].attConst +
			(light[lightIndex].attLinear * lightDist) +
			(light[lightIndex].attQuad * lightDist * lightDist));

		retVal /= attenuation;
	}

	return retVal;
}

vec3 Light_getLightAmbient(uint lightIndex)
{
	return (
		light[lightIndex].albedo *
		light[lightIndex].ambientStrength *
		Light_getLightStrength(lightIndex));
}

float Light_getLightDiffusePower(uint lightIndex, vec3 targetNormal)
{
	return max(dot(targetNormal, -Light_getLightDirection(lightIndex)), 0.f);
}

vec3 Light_getLightDiffuse(uint lightIndex, vec3 targetNormal)
{
	return (
		light[lightIndex].albedo *
		light[lightIndex].diffuseStrength *
		Light_getLightStrength(lightIndex) *
		Light_getLightDiffusePower(lightIndex, targetNormal));
}

float Light_getLightSpecularPower(uint lightIndex, vec3 targetNormal, vec3 viewPos, float materialShininess)
{
	vec3 lightReflection = reflect(Light_getLightDirection(lightIndex), targetNormal);
	vec3 viewDirection = normalize(viewPos - Light_targetPos);

	return pow(max(dot(lightReflection, viewDirection), 0.f), materialShininess);
}

vec3 Light_getLightSpecular(uint lightIndex, vec3 targetNormal, vec3 viewPos, float materialShininess)
{
	return (
		light[lightIndex].albedo *
		light[lightIndex].specularStrength *
		Light_getLightStrength(lightIndex) *
		Light_getLightSpecularPower(lightIndex, targetNormal, viewPos, materialShininess));
}

#endif