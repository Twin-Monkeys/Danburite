//? #version 460 core

#ifndef __LIGHT_HEADER__
#define __LIGHT_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_LIGHT) uniform UBLight
{
	layout(offset = 0) mat4 projViewMat[MAX_NUM_LIGHTS];
	layout(offset = (64 * MAX_NUM_LIGHTS)) vec3 direction[MAX_NUM_LIGHTS];
	layout(offset = (80 * MAX_NUM_LIGHTS)) vec3 pos[MAX_NUM_LIGHTS];
	layout(offset = (96 * MAX_NUM_LIGHTS)) vec3 albedo[MAX_NUM_LIGHTS];
	layout(offset = (112 * MAX_NUM_LIGHTS)) uvec2 depthMap[MAX_NUM_LIGHTS];
	layout(offset = (128 * MAX_NUM_LIGHTS)) bool enabled[MAX_NUM_LIGHTS];
	layout(offset = (144 * MAX_NUM_LIGHTS)) bool shadowEnabled[MAX_NUM_LIGHTS];
	layout(offset = (160 * MAX_NUM_LIGHTS)) uint type[MAX_NUM_LIGHTS];
	layout(offset = (176 * MAX_NUM_LIGHTS)) uint depthBakingType[MAX_NUM_LIGHTS];
	layout(offset = (192 * MAX_NUM_LIGHTS)) float ambientStrength[MAX_NUM_LIGHTS];
	layout(offset = (208 * MAX_NUM_LIGHTS)) float diffuseStrength[MAX_NUM_LIGHTS];
	layout(offset = (224 * MAX_NUM_LIGHTS)) float specularStrength[MAX_NUM_LIGHTS];
	layout(offset = (240 * MAX_NUM_LIGHTS)) float attConst[MAX_NUM_LIGHTS];
	layout(offset = (256 * MAX_NUM_LIGHTS)) float attLinear[MAX_NUM_LIGHTS];
	layout(offset = (272 * MAX_NUM_LIGHTS)) float attQuad[MAX_NUM_LIGHTS];
	layout(offset = (288 * MAX_NUM_LIGHTS)) float validDistance[MAX_NUM_LIGHTS];
	layout(offset = (304 * MAX_NUM_LIGHTS)) float innerCutOff[MAX_NUM_LIGHTS];
	layout(offset = (320 * MAX_NUM_LIGHTS)) float outerCutOff[MAX_NUM_LIGHTS];
	layout(offset = (336 * MAX_NUM_LIGHTS)) float zFar[MAX_NUM_LIGHTS];
	layout(offset = (352 * MAX_NUM_LIGHTS)) uint numLights;
}
light;

uint Light_getNumLights()
{
	return light.numLights;
}

vec3 Light_getLightDirection(const uint lightIndex, const vec3 targetPos)
{
	const uint LIGHT_TYPE = light.type[lightIndex];
	vec3 retVal = vec3(0.f);

	if (LIGHT_TYPE == LIGHT_TYPE_DIRECTIONAL)
	{
		retVal = light.direction[lightIndex];
	}
	else if (
		(LIGHT_TYPE == LIGHT_TYPE_POINT) ||
		(LIGHT_TYPE == LIGHT_TYPE_SPOT))
	{
		retVal = normalize(targetPos - light.pos[lightIndex]);
	}

	return retVal;
}

float Light_getShadowOcclusion_ortho(const uint lightIndex, const vec3 targetPos, const vec3 targetNormal)
{
	const vec4 lightSpaceTargetPos = (light.projViewMat[lightIndex] * vec4(targetPos, 1.f));

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

	const float depthAdjustment =
		max(5e-4f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex, targetPos))), 2e-4f);

	const sampler2D depthMap = sampler2D(light.depthMap[lightIndex]);

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

float Light_getShadowOcclusion_cubemap(const uint lightIndex, const vec3 targetPos, const vec3 targetNormal)
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

	const vec3 lightPosToTarget = (targetPos - light.pos[lightIndex]);
	const float curDepth = length(lightPosToTarget);

	// 광원으로부터 targetPos가 멀어질수록 그림자가 흐려지도록 한다.
	const float biasAdj_lightDistance = pow(curDepth * .01f, 1.5f);

	const float depthAdjustment =
		max(15e-2f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex, targetPos))), 10e-2f);

	const samplerCube depthMap = samplerCube(light.depthMap[lightIndex]);

	float retVal = 0.f;
	for (uint i = 0; i < NUM_SAMPLES; i++)
	{
		const float mappedDepth =
			(texture(depthMap, lightPosToTarget + (sampleBiases[i] * biasAdj_lightDistance)).x * light.zFar[lightIndex]);

		retVal += float(mappedDepth < (curDepth - depthAdjustment));
	}

	// 광원으로부터 targetPos가 멀어질수록 그림자가 옅어지도록 한다.
	retVal *= exp(-curDepth * .005f);

	return (retVal / float(NUM_SAMPLES));
}

float Light_getShadowOcclusion(uint lightIndex, const vec3 targetPos, vec3 targetNormal)
{
	if (!light.shadowEnabled[lightIndex])
		return 0.f;

	if (light.depthBakingType[lightIndex] == LIGHT_DEPTH_BAKING_TYPE_ORTHO)
		return Light_getShadowOcclusion_ortho(lightIndex, targetPos, targetNormal);

	else if (light.depthBakingType[lightIndex] == LIGHT_DEPTH_BAKING_TYPE_CUBEMAP)
		return Light_getShadowOcclusion_cubemap(lightIndex, targetPos, targetNormal);

	return 0.f;
}

float Light_getLightDistance(uint lightIndex, const vec3 targetPos)
{
	return length(targetPos - light.pos[lightIndex]);
}

bool Light_checkValidation(const uint lightIndex, const vec3 targetPos)
{
	if (!light.enabled[lightIndex])
		return false;

	const uint LIGHT_TYPE = light.type[lightIndex];

	if (LIGHT_TYPE == LIGHT_TYPE_SPOT)
	{
		const float lightDist = Light_getLightDistance(lightIndex, targetPos);
		if (lightDist > light.validDistance[lightIndex])
			return false;

		const float theta = dot(light.direction[lightIndex], Light_getLightDirection(lightIndex, targetPos));
		
		const float cutOffValue =
			((theta - light.outerCutOff[lightIndex]) /
			(light.innerCutOff[lightIndex] - light.outerCutOff[lightIndex]));

		if (cutOffValue < 0.f)
			return false;
	}
	else if (LIGHT_TYPE == LIGHT_TYPE_POINT)
	{
		const float lightDist = Light_getLightDistance(lightIndex, targetPos);

		if (lightDist > light.validDistance[lightIndex])
			return false;
	}

	return true;
}

float Light_getAttenuation(uint lightIndex, const vec3 targetPos)
{
	const uint LIGHT_TYPE = light.type[lightIndex];
	float retVal = 1.f;

	if ((LIGHT_TYPE == LIGHT_TYPE_SPOT) || (LIGHT_TYPE == LIGHT_TYPE_POINT))
	{
		const float lightDist = Light_getLightDistance(lightIndex, targetPos);
		const float attenuation =
			(light.attConst[lightIndex] +
			(light.attLinear[lightIndex] * lightDist) +
			(light.attQuad[lightIndex] * lightDist * lightDist));

		retVal /= attenuation;
	}

	return retVal;
}

vec3 Light_getLightAmbient(uint lightIndex, const vec3 targetPos)
{
	return (
		light.albedo[lightIndex] *
		light.ambientStrength[lightIndex]);
}

float Light_getCutOff(const uint lightIndex, const vec3 targetPos)
{
	const uint LIGHT_TYPE = light.type[lightIndex];

	if (LIGHT_TYPE != LIGHT_TYPE_SPOT)
		return 1.f;

	const float theta =
		dot(light.direction[lightIndex], Light_getLightDirection(lightIndex, targetPos));
		
	return clamp(
		(theta - light.outerCutOff[lightIndex]) /
		(light.innerCutOff[lightIndex] - light.outerCutOff[lightIndex]), 0.f, 1.f);
}

float Light_getLightDiffusePower(uint lightIndex, const vec3 targetPos, vec3 targetNormal)
{
	return
		(Light_getCutOff(lightIndex, targetPos) *
		max(dot(targetNormal, -Light_getLightDirection(lightIndex, targetPos)), 0.f));
}

vec3 Light_getLightDiffuse(uint lightIndex, const vec3 targetPos, vec3 targetNormal)
{
	return (
		light.albedo[lightIndex] *
		light.diffuseStrength[lightIndex] *
		Light_getLightDiffusePower(lightIndex, targetPos, targetNormal));
}

float Light_getLightSpecularPower(
	uint lightIndex, const vec3 targetPos, vec3 targetNormal, const vec3 viewDirection, float materialShininess)
{
	//	Traditional Phong specular
	//	vec3 lightReflection = reflect(Light_getLightDirection(lightIndex), targetNormal);
	//	return pow(max(dot(lightReflection, viewDirection), 0.f), materialShininess);

	// Blinn-Phong specular
	vec3 lightDirection = -Light_getLightDirection(lightIndex, targetPos);
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);

	return
		(Light_getCutOff(lightIndex, targetPos) *
		pow(max(dot(targetNormal, halfwayDirection), 0.f), materialShininess));
}

vec3 Light_getLightSpecular(uint lightIndex, const vec3 targetPos, vec3 targetNormal, vec3 viewDirection, float materialShininess)
{
	return (
		light.albedo[lightIndex] *
		light.specularStrength[lightIndex] *
		Light_getLightSpecularPower(lightIndex, targetPos, targetNormal, viewDirection, materialShininess));
}

#endif