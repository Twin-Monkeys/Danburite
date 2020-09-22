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
	layout(offset = (368 * MAX_NUM_LIGHTS)) uint numLights;
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
	const uint NUM_SAMPLES = 20U;
	const vec2 sampleBiases[] = vec2[]
	(
		.002f * vec2(.542641f, -.402478f),
		.002f * vec2(-.0108202f, .267296f),
		.002f * vec2(.497608f, .663823f),
		.002f * vec2(.166644f, -.550407f),
		.002f * vec2(-.603874f, .418416f),

		.002f * vec2(-.468868f, -.661778f),
		.002f * vec2(-.82332f, -.699244f),
		.002f * vec2(.367637f, .906787f),
		.002f * vec2(-.992103f, -.327857f),
		.002f * vec2(.781633f, .625242f),

		.002f * vec2(.225052f, -.938767f),
		.002f * vec2(.75523f, -.416248f),
		.002f * vec2(.835548f, .0817618f),
		.002f * vec2(-.737084f, .0850887f),
		.002f * vec2(-.71566f, .557458f),

		.002f * vec2(.167803f, .348267f),
		.002f * vec2(-.116334f, .652164f),
		.002f * vec2(-.789196f, .235534f),
		.002f * vec2(.0262765f, -.868873f),
		.002f * vec2(-.887112f, .202078f)
	);

	vec3 normalizedPos = (light.projViewMat[lightIndex] * vec4(targetPos, 1.f)).xyz;

	// Map the value [-1, 1] to [0, 1]
	normalizedPos = ((normalizedPos * .5f) + .5f);
	if (normalizedPos.z >= 1.f)
		return 0.f;

	const float depthScaleFactor = (light.zFar[lightIndex] - light.zNear[lightIndex]);

	/*
		제대로 된 depth 값은 zNear도 더해주어야 하지만,
		이곳의 로직에서는 depth 간 대소비교만 수행하기 때문에
		따로 더해주지 않았다.
	*/
	const float receiverDepth = (normalizedPos.z * depthScaleFactor);
	const sampler2D depthMap = sampler2D(light.depthMap[lightIndex]);
	
	float blockerDepthAvg = 0.f;
	uint numBlockers = 0U;

	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			const float blockerDepth =
				(texture(depthMap, normalizedPos.xy + vec2(.001f * i, .001f * j)).x * depthScaleFactor);

			// if blocked
			if (blockerDepth < receiverDepth)
			{
				blockerDepthAvg += blockerDepth;
				numBlockers++;
			}
		}
	}

	// preprocess
	if (numBlockers == 0)
		return 0.f;
	else if (numBlockers == NUM_SAMPLES)
		return 1.f;

	blockerDepthAvg /= float(numBlockers);

	const float lightWidth = 10.f;
	const float penumbra = (((receiverDepth - blockerDepthAvg) * lightWidth) / blockerDepthAvg);

	float retVal = 0.f;
	for (uint i = 0U; i < NUM_SAMPLES; i++)
	{
		const float blockerDepth =
			(texture(depthMap, normalizedPos.xy + (sampleBiases[i] * penumbra)).x * depthScaleFactor);

		retVal += float(blockerDepth < receiverDepth);
	}

	retVal /= float(NUM_SAMPLES);
	return retVal;
}

float Light_getShadowOcclusion_cubemap(const uint lightIndex, const vec3 targetPos, const vec3 targetNormal)
{
	const float zFar = light.zFar[lightIndex];

	const vec3 lightPosToTarget = (targetPos - light.pos[lightIndex]);
	const float receiverDepth = length(lightPosToTarget);

	const samplerCube depthMap = samplerCube(light.depthMap[lightIndex]);

	float blockerDepthAvg = 0.f;
	uint numBlockers = 0U;

	const vec3 lightDir = normalize(lightPosToTarget);
	const vec3 horiz = normalize(vec3
	(
		lightDir.y - lightDir.z,
		lightDir.z - lightDir.x,
		lightDir.x - lightDir.y
	));

	const vec3 vert = cross(lightDir, horiz);

	for (int j = -2; j <= 2; j++)
		for (int k = -2; k <= 2; k++)
		{
			// 충분한 bias가 있어야 부드러운 shadow 블렌딩이 가능하다.
			// 하지만 너무 크면 light width가 커지면서 이상한 아티팩트가 생김.
			const float blockerDepth =
				(texture(depthMap, lightDir + (.07f * ((horiz * j) + (vert * k)))).x * zFar);

			// if blocked
			if (blockerDepth < receiverDepth)
			{
				blockerDepthAvg += blockerDepth;
				numBlockers++;
			}
		}

	// preprocess
	if (numBlockers == 0)
		return 0.f;
	else if (numBlockers == 25)
		return 1.f;

	blockerDepthAvg /= float(numBlockers);

	const float lightWidth = 5.f;
	const float penumbra = (((receiverDepth - blockerDepthAvg) * lightWidth) / blockerDepthAvg);

	// 샘플링 횟수가 많아야 블렌딩이 층지지 않고 부드럽게 나옴.
	float retVal = 0.f;
	for (int i = -2; i <= 2; i++)
		for (int j = -2; j <= 2; j++)
		{
			const float mappedDepth =
				(texture(depthMap, lightPosToTarget + (.001f * receiverDepth * (horiz * i + vert + j) * penumbra)).x * zFar);

			retVal += float(mappedDepth < receiverDepth);
		}

	retVal /= 25.f;
	retVal *= retVal;
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