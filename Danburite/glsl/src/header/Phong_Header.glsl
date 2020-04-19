//? #version 460 core

#ifndef __PHONG_HEADER__
#define __PHONG_HEADER__

#include "Light_Header.glsl"
#include "Material_Header.glsl"
#include "Camera_Header.glsl"

vec3 Phong_calcAmbient(uint lightIdx, vec3 materialAmbient)
{
	return (materialAmbient * Light_getLightAmbient(lightIdx));
}

vec3 Phong_calcDiffuse(uint lightIdx, vec3 materialDiffuse, vec3 targetNormal)
{
	return (materialDiffuse * Light_getLightDiffuse(lightIdx, targetNormal));
}

vec3 Phong_calcSpecular(uint lightIdx, vec3 materialSpecular, vec3 targetNormal, float materialShininess)
{
	return (
		materialSpecular *
		Light_getLightSpecular(lightIdx, targetNormal, Camera_getPosition(), materialShininess));
}
 
vec4 Phong_calcPhongColor(
	const vec3 targetPos, const vec3 targetNormal, const mat3 targetTBN,
	const vec2 materialTexCoord, const vec4 vertexColor)
{
	Light_setLightTargetPos(targetPos);

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

	for (uint i = 0; i < MAX_NUM_LIGHTS; i++)
	{
		if (!Light_isLightEnabled(i))
			continue;

		ambient += Phong_calcAmbient(i, materialAmbient);

		const float lightOcclusion = Light_getOcclusion(i, materialNormal);
		if (lightOcclusion >= 1.f)
			continue;

		diffuse += ((1.f - lightOcclusion) * Phong_calcDiffuse(i, materialDiffuse, materialNormal));
		specular += ((1.f - lightOcclusion) * Phong_calcSpecular(i, materialSpecular, materialNormal, materialShininess));
	}

	return vec4(ambient + diffuse + specular + materialEmissive, materialAlpha);
}

#endif