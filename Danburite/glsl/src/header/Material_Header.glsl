//? #version 460 core

#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#include "Constant_Header.glsl"

struct Material
{
	uint type;
	uint optionFlag;
	uint vertexFlag;

	vec4 diffuseColor;
	float shininess;

	sampler2D ambientTex;
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D emissiveTex;
	sampler2D shininessTex;
	sampler2D alphaTex;
	sampler2D normalTex;

	float zNear;
	float zFar;

	vec4 outlineColor;
	float thicknessRatio;

	samplerCube environmentTex;
};

uniform Material material;

vec2 Material_texCoord;
vec3 Material_targetNormal;

void Material_setTexCoord(vec2 texCoord)
{
	Material_texCoord = texCoord;
}

void Material_setTargetNormal(vec3 normal)
{
	Material_targetNormal = normal;
}

bool Material_isLightingEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_LIGHTING) != 0);
}

bool Material_isShininessTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_SHININESS_TEXTURE) != 0);
}

bool Material_isAlphaTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_ALPHA_TEXTURE) != 0);
}

bool Material_isNormalTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_NORMAL_TEXTURE) != 0);
}

bool Material_isVertexPositionEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_POS3) != 0);
}

bool Material_isVertexColorEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_COLOR4) != 0);
}

bool Material_isVertexNormalEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_NORMAL3) != 0);
}

bool Material_isVertexTexCoordEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_TEXCOORD2) != 0);
}

vec3 Material_getAmbient()
{
	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
			return texture(material.ambientTex, Material_texCoord).rgb;
	}

	return vec3(0.f);
}

vec3 Material_getDiffuse()
{
	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
			return texture(material.diffuseTex, Material_texCoord).rgb;
	}

	return vec3(0.f);
}

vec3 Material_getSpecular()
{
	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
			return texture(material.specularTex, Material_texCoord).rgb;
	}

	return vec3(0.f);
}

vec3 Material_getEmissive()
{
	if (
		(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
		(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
		(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
		(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
		(material.type == MATERIAL_TYPE_PHONG))
		return texture(material.emissiveTex, Material_texCoord).rgb;

	return vec3(0.f);
}

float Material_getShininess()
{
	if (Material_isShininessTextureEnabled())
		return texture(material.shininessTex, Material_texCoord).r;

	return material.shininess;
}

float Material_getAlpha()
{
	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.a;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
			{
				if (Material_isAlphaTextureEnabled())
					return texture(material.alphaTex, Material_texCoord).r;
				else
					return texture(material.diffuseTex, Material_texCoord).a;
			}
	}

	return 1.f;
}

vec3 Material_getNormal()
{
	//if (isMaterialNormalTextureEnabled())
	//	return texture(material.normalTex, Material_texCoord).xyz;

	return Material_targetNormal;
}

float Material_getLinearDepth(float fragDepth)
{
	const float ndcDepth = ((fragDepth * 2.f) - 1.f);
	const float linearDepth = (
		(2.f * material.zNear * material.zFar) /
		((material.zNear + material.zFar) + (ndcDepth * (material.zNear - material.zFar))));

	return (linearDepth / material.zFar);
}

vec4 Material_getEnvReflection(vec3 targetPos, vec3 viewPos)
{
	vec3 viewDirection = normalize(targetPos - viewPos);
	vec3 reflection = reflect(viewDirection, Material_getNormal());

	return texture(material.environmentTex, reflection);
}

vec4 Material_getEnvRefraction(vec3 targetPos, vec3 viewPos)
{
	vec3 viewDirection = normalize(targetPos - viewPos);
	vec3 refraction = refract(viewDirection, Material_getNormal(), 1.f / 1.52f);

	return texture(material.environmentTex, refraction);
}

#endif