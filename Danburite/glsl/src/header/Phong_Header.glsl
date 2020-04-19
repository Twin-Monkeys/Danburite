//? #version 460 core

#ifndef __PHONG_HEADER__
#define __PHONG_HEADER__

#include "Light_Header.glsl"
#include "Material_Header.glsl"
#include "Camera_Header.glsl"
 
vec4 Phong_calcPhongColor(
	const vec3 targetPos, const vec3 targetNormal, const mat3 targetTBN,
	const vec2 materialTexCoord, const vec4 vertexColor)
{
	vec3 materialAmbient = Material_getAmbient(materialTexCoord);
	vec3 materialDiffuse = Material_getDiffuse(materialTexCoord);
	vec3 materialSpecular = Material_getSpecular(materialTexCoord);
	vec3 materialEmissive = Material_getEmissive(materialTexCoord);
	float materialAlpha = Material_getAlpha(materialTexCoord);

	if (Material_isVertexColorEnabled())
	{
		materialAmbient += vertexColor.rgb;
		materialDiffuse += vertexColor.rgb;
		materialSpecular += vertexColor.rgb;
		materialAlpha += ((1.f - materialAlpha) * vertexColor.a);
	}

	if (!Material_isLightingEnabled())
		return vec4(materialAmbient + materialDiffuse + materialSpecular + materialEmissive, materialAlpha);

	const float materialShininess = Material_getShininess(materialTexCoord);
	const vec3 materialNormal = Material_getNormal(materialTexCoord, targetNormal, targetTBN);

	vec3 ambient = vec3(0.f);
	vec3 diffuse = vec3(0.f);
	vec3 specular = vec3(0.f);

	const vec3 viewPos = Camera_getPosition();
	for (uint lightIdx = 0; lightIdx < MAX_NUM_LIGHTS; lightIdx++)
	{
		if (!Light_isLightEnabled(lightIdx))
			continue;

		ambient += (materialAmbient * Light_getLightAmbient(lightIdx, targetPos));

		const float lightOcclusion = Light_getOcclusion(lightIdx, targetPos, materialNormal);
		if (lightOcclusion >= 1.f)
			continue;

		const float occlusionInv = (1.f - lightOcclusion);

		diffuse += (
			occlusionInv * materialDiffuse *
			Light_getLightDiffuse(lightIdx, targetPos, materialNormal));

		specular += (
			occlusionInv * materialSpecular *
			Light_getLightSpecular(lightIdx, targetPos, materialNormal, viewPos, materialShininess));
	}

	return vec4(ambient + diffuse + specular + materialEmissive, materialAlpha);
}

#endif