//? #version 460 core

#ifndef __LIGHT_HEADER__
#define __LIGHT_HEADER__

#extension GL_ARB_bindless_texture : require

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

	// shadow
	bool shadowEnabled;
	uint depthBakingType;
	uvec2 depthMap;

	// ortho depth baking
	mat4 projViewMat;

	// cubemap depth baking
	float zFar;
};

layout(binding = BINDING_POINT_LIGHT) uniform UBLight
{
	Light light[MAX_NUM_LIGHTS];
};

vec3 Light_targetPos;

bool Light_isLightEnabled(uint lightIndex)
{
	return light[lightIndex].enabled;
}

void Light_setLightTargetPos(vec3 targetPos)
{
	Light_targetPos = targetPos;
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

float Light_getOcclusion_ortho(const uint lightIndex, const vec3 targetNormal)
{
	const vec4 lightSpaceTargetPos = (light[lightIndex].projViewMat * vec4(Light_targetPos, 1.f));

	/*
		When using an orthographic projection matrix
		The w component of a vertex remains untouched so this step is actually quite meaningless.
		However, it is necessary when using perspective projection so keeping this line
		Ensures it works with both projection matrices.
	*/
	vec3 normalizedPos = (lightSpaceTargetPos.xyz / lightSpaceTargetPos.w);

	// Map the value [-1, 1] to [0, 1]
	normalizedPos = ((normalizedPos * .5f) + .5f);
	if (normalizedPos.z >= 1.f)
		return 0.f;

	const float depthAdjustment = max(5e-4f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex))), 2e-4f);
	const sampler2D depthMap = sampler2D(light[lightIndex].depthMap);

	float retVal = 0.f;
	for (int x = -1; x <= 1; x++)
		for (int y = -1; y <= 1; y++)
		{
			const float mappedDepth = texture(depthMap, normalizedPos.xy + (vec2(x, y) * .01f)).x;

			// To correct shadow acne issue change the amount of bias based on the surface angle towards the light
			retVal += float(mappedDepth < (normalizedPos.z - depthAdjustment));
		}

	return (retVal / 9.f);
}

float Light_getOcclusion_cubemap(const uint lightIndex, const vec3 targetNormal)
{
	const uint NUM_SAMPLES = 20U;
	const vec3 sampleBiases[NUM_SAMPLES] = vec3[]
	(
	   vec3( 1.f,  1.f,  1.f), vec3( 1.f, -1.f,  1.f), vec3(-1.f, -1.f,  1.f), vec3(-1.f,  1.f,  1.f), 
	   vec3( 1.f,  1.f, -1.f), vec3( 1.f, -1.f, -1.f), vec3(-1.f, -1.f, -1.f), vec3(-1.f,  1.f, -1.f),
	   vec3( 1.f,  1.f,  0.f), vec3( 1.f, -1.f,  0.f), vec3(-1.f, -1.f,  0.f), vec3(-1.f,  1.f,  0.f),
	   vec3( 1.f,  0.f,  1.f), vec3(-1.f,  0.f,  1.f), vec3( 1.f,  0.f, -1.f), vec3(-1.f,  0.f, -1.f),
	   vec3( 0.f,  1.f,  1.f), vec3( 0.f, -1.f,  1.f), vec3( 0.f, -1.f, -1.f), vec3( 0.f,  1.f, -1.f)
	);

	const vec3 lightPosToTarget = (Light_targetPos - light[lightIndex].pos);
	const float curDepth = length(lightPosToTarget);

	// 광원으로부터 물체가 멀어질수록 그림자가 흐려지도록 한다.
	const float biasAdj_lightDistance = (pow(curDepth / light[lightIndex].zFar, 1.5f) * 20.f);

	const float depthAdjustment = max(15e-2f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex))), 10e-2f);
	const samplerCube depthMap = samplerCube(light[lightIndex].depthMap);

	float retVal = 0.f;
	for (uint i = 0; i < NUM_SAMPLES; i++)
	{
		const float mappedDepth =
			(texture(depthMap, lightPosToTarget + (sampleBiases[i] * biasAdj_lightDistance)).x * light[lightIndex].zFar);

		retVal += float(mappedDepth < (curDepth - depthAdjustment));
	}

	return (retVal / float(NUM_SAMPLES));
}

float Light_getOcclusion(uint lightIndex, vec3 targetNormal)
{
	if (!light[lightIndex].shadowEnabled)
		return 0.f;

	if (light[lightIndex].depthBakingType == LIGHT_DEPTH_BAKING_TYPE_ORTHO)
		return Light_getOcclusion_ortho(lightIndex, targetNormal);

	else if (light[lightIndex].depthBakingType == LIGHT_DEPTH_BAKING_TYPE_CUBEMAP)
		return Light_getOcclusion_cubemap(lightIndex, targetNormal);

	return 0.f;
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
	//	Traditional Phong specular
	//	vec3 lightReflection = reflect(Light_getLightDirection(lightIndex), targetNormal);
	//	vec3 viewDirection = normalize(viewPos - Light_targetPos);
	//
	//	return pow(max(dot(lightReflection, viewDirection), 0.f), materialShininess);

	// Blinn-Phong specular
	vec3 lightDirection = -Light_getLightDirection(lightIndex);
	vec3 viewDirection = normalize(viewPos - Light_targetPos);
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);

	return pow(max(dot(targetNormal, halfwayDirection), 0.f), materialShininess);
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