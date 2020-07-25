//? #version 460 core

#ifndef __PHONG_HEADER__
#define __PHONG_HEADER__

#include "Light_Header.glsl"
#include "Material_Header.glsl"
#include "Camera_Header.glsl"
 
vec4 Phong_calcPhongColor(
	const vec3 targetPos, const vec3 targetNormal, const mat3 targetTBN,
	const vec2 targetTexCoord, const vec4 vertexColor)
{
	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - targetPos);

	const vec2 finalTexCoord = Material_getTexCoord(targetTexCoord, viewDir, targetTBN);

	vec3 materialAmbient = Material_getAmbient(finalTexCoord);
	vec3 materialDiffuse = Material_getDiffuse(finalTexCoord);
	vec3 materialSpecular = Material_getSpecular(finalTexCoord);
	vec3 materialEmissive = Material_getEmissive(finalTexCoord);
	const float materialAlpha = Material_getAlpha(finalTexCoord);

	if (Material_isVertexColorEnabled())
	{
		materialAmbient *= vertexColor.rgb;
		materialDiffuse *= vertexColor.rgb;
		materialSpecular *= vertexColor.rgb;
	}

	if (!Material_isLightingEnabled())
		return vec4(materialAmbient + materialDiffuse + materialSpecular + materialEmissive, materialAlpha);

	const float shininess = Material_getShininess(finalTexCoord);
	const vec3 finalNormal = Material_getNormal(finalTexCoord, targetNormal, targetTBN);

	vec3 ambient = vec3(0.f);
	vec3 diffuse = vec3(0.f);
	vec3 specular = vec3(0.f);

	for (uint lightIdx = 0; lightIdx < MAX_NUM_LIGHTS; lightIdx++)
	{
		if (!Light_isLightEnabled(lightIdx))
			continue;

		ambient += (materialAmbient * Light_getLightAmbient(lightIdx, targetPos));

		const float lightOcclusion = Light_getOcclusion(lightIdx, targetPos, finalNormal);
		if (lightOcclusion >= 1.f)
			continue;

		const float occlusionInv = (1.f - lightOcclusion);

		diffuse += (
			occlusionInv * materialDiffuse *
			Light_getLightDiffuse(lightIdx, targetPos, finalNormal));

		specular += (
			occlusionInv * materialSpecular *
			Light_getLightSpecular(lightIdx, targetPos, finalNormal, viewDir, shininess));
	}

	return vec4(ambient + diffuse + specular + materialEmissive, materialAlpha);
}

#endif