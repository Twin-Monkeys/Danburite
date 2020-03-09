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

	// texture handle
	uvec2 ambientTex;
	uvec2 diffuseTex;
	uvec2 specularTex;
	uvec2 emissiveTex;
	uvec2 shininessTex;
	uvec2 alphaTex;
	uvec2 normalTex;
	uvec2 environmentTex;

	float zNear;
	float zFar;

	vec4 outlineColor;
	float thicknessRatio;

};

layout (binding = BINDING_POINT_MATERIAL) uniform UBMaterial
{
	Material material;
};

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

bool Material_isDiffuseTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_DIFFUSE_TEXTURE) != 0);
}

bool Material_isSpecularTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_SPECULAR_TEXTURE) != 0);
}

bool Material_isEmissiveTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_EMISSIVE_TEXTURE) != 0);
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
				retVal = texture(sampler2D(material.ambientTex), Material_texCoord).rgb;
			else if (Material_isDiffuseTextureEnabled())
			{
				retVal = texture(sampler2D(material.diffuseTex), Material_texCoord).rgb;
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
			(material.type == MATERIAL_TYPE_PHONG) &&
			Material_isDiffuseTextureEnabled())
		{
			retVal = texture(sampler2D(material.diffuseTex), Material_texCoord).rgb;
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
				retVal = texture(sampler2D(material.specularTex), Material_texCoord).rgb;
			else if (Material_isDiffuseTextureEnabled())
			{
				retVal = texture(sampler2D(material.diffuseTex), Material_texCoord).rgb;
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
		if (Material_isEmissiveTextureEnabled())
		{
			retVal = texture(sampler2D(material.emissiveTex), Material_texCoord).rgb;
			retVal = Material_applyGamma(retVal);
		}
	}

	return retVal;
}

float Material_getShininess()
{
	if (Material_isShininessTextureEnabled())
		return texture(sampler2D(material.shininessTex), Material_texCoord).r;

	return material.shininess;
}

float Material_getAlpha()
{
	float retVal = 1.f;

	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		retVal = material.diffuseColor.a;
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
					retVal = texture(sampler2D(material.alphaTex), Material_texCoord).r;
				else if (Material_isDiffuseTextureEnabled())
					retVal = texture(sampler2D(material.diffuseTex), Material_texCoord).a;
			}
	}

	return retVal;
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

	vec4 retVal = texture(samplerCube(material.environmentTex), reflection);

	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

vec4 Material_getEnvRefraction(vec3 targetPos, vec3 viewPos)
{
	vec3 viewDirection = normalize(targetPos - viewPos);
	vec3 refraction = refract(viewDirection, Material_getNormal(), 1.f / 1.52f);

	vec4 retVal = texture(samplerCube(material.environmentTex), refraction);

	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

#endif