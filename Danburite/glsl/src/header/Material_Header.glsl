//? #version 460 core

#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

struct Material
{
	uint type;
	uint optionFlag;
	uint vertexFlag;

	vec4 diffuseColor;
	float gamma;

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

bool Material_isAmbientTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_AMBIENT_TEXTURE) != 0);
}

bool Material_isSpecularTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_SPECULAR_TEXTURE) != 0);
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

vec3 Material_applyGamma(const vec3 source)
{
	return pow(source, vec3(material.gamma));
}

vec3 Material_getAmbient()
{
	vec3 retVal = vec3(0.f);

	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		retVal = material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
		{
			if (Material_isAmbientTextureEnabled())
				retVal = texture(material.ambientTex, Material_texCoord).rgb;
			else
			{
				retVal = texture(material.diffuseTex, Material_texCoord).rgb;
				retVal = Material_applyGamma(retVal);
			}
		}
	}

	return retVal;
}

vec3 Material_getDiffuse()
{
	vec3 retVal = vec3(0.f);

	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		retVal = material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
		{
			retVal = texture(material.diffuseTex, Material_texCoord).rgb;
			retVal = pow(retVal, vec3(material.gamma));
		}
	}

	return retVal;
}

vec3 Material_getSpecular()
{
	vec3 retVal = vec3(0.f);

	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		retVal = material.diffuseColor.rgb;
	else
	{
		if (
			(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
			(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
			(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
			(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
			(material.type == MATERIAL_TYPE_PHONG))
		{
			if (Material_isSpecularTextureEnabled())
				retVal = texture(material.specularTex, Material_texCoord).rgb;
			else
			{
				retVal = texture(material.diffuseTex, Material_texCoord).rgb;
				retVal = Material_applyGamma(retVal);
			}
		}
	}

	return retVal;
}

vec3 Material_getEmissive()
{
	vec3 retVal = vec3(0.f);

	if (
		(material.type == MATERIAL_TYPE_EXPLODING_PHONG) ||
		(material.type == MATERIAL_TYPE_REFLECTION_PHONG) ||
		(material.type == MATERIAL_TYPE_TRANSPARENT_PHONG) ||
		(material.type == MATERIAL_TYPE_OUTLINING_PHONG) ||
		(material.type == MATERIAL_TYPE_PHONG))
	{
		retVal = texture(material.emissiveTex, Material_texCoord).rgb;
		retVal = Material_applyGamma(retVal);
	}

	return retVal;
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

	vec4 retVal = texture(material.environmentTex, reflection);

	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

vec4 Material_getEnvRefraction(vec3 targetPos, vec3 viewPos)
{
	vec3 viewDirection = normalize(targetPos - viewPos);
	vec3 refraction = refract(viewDirection, Material_getNormal(), 1.f / 1.52f);

	vec4 retVal = texture(material.environmentTex, refraction);

	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

#endif