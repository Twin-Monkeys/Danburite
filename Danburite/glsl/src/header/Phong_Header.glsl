//? #version 460 core

#ifndef __PHONG_HEADER__
#define __PHONG_HEADER__

#include "Light_Header.glsl"
#include "Material_Header.glsl"
#include "Camera_Header.glsl"
#include "LightPrePass_Header.glsl"

layout(std140, binding = BINDING_POINT_PHONG) uniform UBPhong
{
	layout(offset = 0) uint calcMethodType;
}
phong;

vec4 Phong_calcPhongColor_forward(
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

	vec4 shadedColor;

	if (Material_isLightingEnabled())
	{
		const float shininess = Material_getShininess(finalTexCoord);
		const vec3 finalNormal = Material_getNormal(finalTexCoord, targetNormal, targetTBN);

		vec3 ambient = vec3(0.f);
		vec3 diffuse = vec3(0.f);
		vec3 specular = vec3(0.f);

		const uint NUM_LIGHTS = Light_getNumLights();
		for (uint lightIdx = 0; lightIdx < NUM_LIGHTS; lightIdx++)
		{
			if (!Light_checkValidation(lightIdx, targetPos))
				continue;

			const float lightAttenuation = Light_getAttenuation(lightIdx, targetPos);

			ambient += (
				materialAmbient * lightAttenuation *
				Light_getLightAmbient(lightIdx, targetPos));

			const float lightOcclusion = Light_getOcclusion(lightIdx, targetPos, finalNormal);
			if (lightOcclusion >= 1.f)
				continue;

			const float occlusionInv = (1.f - lightOcclusion);

			diffuse += (
				occlusionInv * materialDiffuse * lightAttenuation *
				Light_getLightDiffuse(lightIdx, targetPos, finalNormal));

			specular += (
				occlusionInv * materialSpecular * lightAttenuation *
				Light_getLightSpecular(lightIdx, targetPos, finalNormal, viewDir, shininess));
		}

		shadedColor = vec4(ambient + diffuse + specular + materialEmissive, materialAlpha);
	}
	else
	{
		shadedColor = vec4(
			materialAmbient + materialDiffuse + materialSpecular + materialEmissive, materialAlpha);
	}
	
	return vec4(shadedColor.rgb * Material_getOcclusion(finalTexCoord), shadedColor.a);
}

vec4 Phong_calcPhongColor_lightPrePass(
	const vec3 targetPos, const mat3 targetTBN, const vec2 targetTexCoord, const vec4 vertexColor)
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

	vec4 shadedColor;

	if (Material_isLightingEnabled())
	{
		const vec3 ambient = (materialAmbient * LightPrePass_getLightAmbient(gl_FragCoord.xy));
		const vec3 diffuse = (materialDiffuse * LightPrePass_getLightDiffuse(gl_FragCoord.xy));
		const vec3 specular = (materialSpecular * LightPrePass_getLightSpecular(gl_FragCoord.xy));
		
		shadedColor = vec4(ambient + diffuse + specular + materialEmissive, materialAlpha);
	}
	else
	{
		shadedColor = vec4(
			materialAmbient + materialDiffuse + materialSpecular + materialEmissive, materialAlpha);
	}

	return vec4(shadedColor.rgb * Material_getOcclusion(finalTexCoord), shadedColor.a);
}

vec4 Phong_calcPhongColor(
	const vec3 targetPos, const vec3 targetNormal, const mat3 targetTBN,
	const vec2 targetTexCoord, const vec4 vertexColor)
{
	if (phong.calcMethodType == PHONG_CALC_METHOD_TYPE_FORWARD)
		return Phong_calcPhongColor_forward(targetPos, targetNormal, targetTBN, targetTexCoord, vertexColor);

	else if (phong.calcMethodType == PHONG_CALC_METHOD_TYPE_LIGHT_PREPASS)
		return Phong_calcPhongColor_lightPrePass(targetPos, targetTBN, targetTexCoord, vertexColor);

	return vec4(0.f);
}

#endif