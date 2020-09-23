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
	layout(offset = (336 * MAX_NUM_LIGHTS)) float zNear[MAX_NUM_LIGHTS];
	layout(offset = (352 * MAX_NUM_LIGHTS)) float zFar[MAX_NUM_LIGHTS];
	layout(offset = (368 * MAX_NUM_LIGHTS)) float width[MAX_NUM_LIGHTS];
	layout(offset = (384 * MAX_NUM_LIGHTS)) uint shadowKernelRange[MAX_NUM_LIGHTS];
	layout(offset = (400 * MAX_NUM_LIGHTS)) uint numLights;
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
	const sampler2D depthMap = sampler2D(light.depthMap[lightIndex]);

	const float lightWidth = light.width[lightIndex];
	const float depthScaleFactor = (light.zFar[lightIndex] - light.zNear[lightIndex]);

	const int kernelRange = int(light.shadowKernelRange[lightIndex]);
	const int kernelSize = ((kernelRange * 2) + 1);
	const int numKernels = (kernelSize * kernelSize);

	/*
		샘플링 횟수가 많아야 블렌딩이 층지지 않고 부드럽게 나옴.
		또한 충분한 bias가 있어야 부드러운 shadow 블렌딩이 가능하다.
		하지만 너무 크면 이상한 아티팩트가 생김.
	*/
	const float blockerSearchingStep = (.06f / float(kernelRange));
	const float pcfStep = (blockerSearchingStep * .07f);

	vec3 normalizedPos = (light.projViewMat[lightIndex] * vec4(targetPos, 1.f)).xyz;

	// Map the value [-1, 1] to [0, 1]
	normalizedPos = ((normalizedPos * .5f) + .5f);
	if (normalizedPos.z >= 1.f)
		return 0.f;

	const float receiverDepth = (normalizedPos.z * depthScaleFactor);
	
	float blockerDepthAvg = 0.f;
	int numBlockers = 0;
	for (int horizIter = -kernelRange; horizIter <= kernelRange; horizIter++)
		for (int vertIter = -kernelRange; vertIter <= kernelRange; vertIter++)
		{
			const vec2 coordOffset = (blockerSearchingStep * vec2(horizIter, vertIter));
			const float blockerDepth = (texture(depthMap, normalizedPos.xy + coordOffset).x * depthScaleFactor);

			if (blockerDepth < receiverDepth)
			{
				blockerDepthAvg += blockerDepth;
				numBlockers++;
			}
		}

	if (numBlockers == 0)
		return 0.f;
	else if (numBlockers == numKernels)
		return 1.f;

	blockerDepthAvg /= float(numBlockers);

	const float penumbra = (((receiverDepth - blockerDepthAvg) * (pcfStep * lightWidth)) / blockerDepthAvg);

	const float depthAdjustment =
		max(.015f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex, targetPos))), .001f);

	float retVal = 0.f;
	for (int horizIter = -kernelRange; horizIter <= kernelRange; horizIter++)
		for (int vertIter = -kernelRange; vertIter <= kernelRange; vertIter++)
		{
			const vec2 coordOffset = (penumbra * vec2(horizIter, vertIter));
			const float blockerDepth = (texture(depthMap, normalizedPos.xy + coordOffset).x * depthScaleFactor);

			retVal += float(blockerDepth < (receiverDepth + depthAdjustment));
		}

	retVal /= float(numKernels);
	return retVal;
}

float Light_getShadowOcclusion_cubemap(const uint lightIndex, const vec3 targetPos, const vec3 targetNormal)
{
	const samplerCube depthMap = samplerCube(light.depthMap[lightIndex]);

	const float lightWidth = light.width[lightIndex];
	const float zFar = light.zFar[lightIndex];

	const int kernelRange = int(light.shadowKernelRange[lightIndex]);
	const int kernelSize = ((kernelRange * 2) + 1);
	const int numKernels = (kernelSize * kernelSize);

	/*
		샘플링 횟수가 많아야 블렌딩이 층지지 않고 부드럽게 나옴.
		또한 충분한 bias가 있어야 부드러운 shadow 블렌딩이 가능하다.
		하지만 너무 크면 이상한 아티팩트가 생김.
	*/
	const float blockerSearchingStep = (.06f / float(kernelRange));
	const float pcfStep = (blockerSearchingStep * .07f);

	const vec3 lightPosToTarget = (targetPos - light.pos[lightIndex]);
	const float receiverDepth = length(lightPosToTarget);

	const vec3 lightForward = normalize(lightPosToTarget);
	const vec3 lightHoriz = normalize(vec3
	(
		lightForward.y - lightForward.z,
		lightForward.z - lightForward.x,
		lightForward.x - lightForward.y
	));

	const vec3 lightVert = cross(lightForward, lightHoriz);

	float blockerDepthAvg = 0.f;
	int numBlockers = 0;
	for (int horizIter = -kernelRange; horizIter <= kernelRange; horizIter++)
		for (int vertIter = -kernelRange; vertIter <= kernelRange; vertIter++)
		{
			const vec3 coordOffset = (blockerSearchingStep * ((lightHoriz * horizIter) + (lightVert * vertIter)));
			const float blockerDepth =(texture(depthMap, lightForward + coordOffset).x * zFar);

			if (blockerDepth < receiverDepth)
			{
				blockerDepthAvg += blockerDepth;
				numBlockers++;
			}
		}

	if (numBlockers == 0)
		return 0.f;
	else if (numBlockers == numKernels)
		return 1.f;

	blockerDepthAvg /= float(numBlockers);

	const float penumbra = (((receiverDepth - blockerDepthAvg) * (pcfStep * lightWidth)) / blockerDepthAvg);

	const float depthAdjustment =
		max(.015f * (1.f - dot(targetNormal, -Light_getLightDirection(lightIndex, targetPos))), .001f);

	float retVal = 0.f;
	for (int horizIter = -kernelRange; horizIter <= kernelRange; horizIter++)
		for (int vertIter = -kernelRange; vertIter <= kernelRange; vertIter++)
		{
			const vec3 coordOffset = (penumbra * ((lightHoriz * horizIter) + (lightVert * vertIter)));
			const float blockerDepth =(texture(depthMap, lightForward + coordOffset).x * zFar);

			retVal += float(blockerDepth < (receiverDepth + depthAdjustment));
		}

	retVal /= float(numKernels);
	return retVal;
}

float Light_getShadowOcclusion(const uint lightIndex, const vec3 targetPos, const vec3 targetNormal)
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