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
	uvec2 heightTex;
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

bool Material_isHeightTextureEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_HEIGHT_TEXTURE) != 0);
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

bool Material_isVertexTangentEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_TANGENT3) != 0);
}

vec3 Material_applyGamma(const vec3 source)
{
	return pow(source, vec3(material.gamma));
}

vec2 Material_getTexCoord(const vec2 vertexTexCoord, const vec3 viewDirection, const mat3 TBN)
{
	if (!Material_isHeightTextureEnabled())
		return vertexTexCoord;

	const sampler2D heightTex = sampler2D(material.heightTex);
	const vec3 tangentSpaceViewDir = (transpose(TBN) * viewDirection);

	const float MIN_NUM_LAYERS = 15.f;
	const float MAX_NUM_LAYERS = 80.f;
	const float NUM_LAYERS = mix(MAX_NUM_LAYERS, MIN_NUM_LAYERS, abs(tangentSpaceViewDir.z));

	const float stepDepth = (1.f / NUM_LAYERS);

	// Parallax mapping with offset limiting
	const vec2 stepOffset = ((-tangentSpaceViewDir.xy / tangentSpaceViewDir.z) * (stepDepth * .1f));

	vec2 curTexCoord = vertexTexCoord;
	vec2 prevTexCoord = vertexTexCoord;

	float curLayerDepth = 0.f;
	float prevLayerDepth = 0.f;

	float curMappedDepth = 0.f;
	float prevMappedDepth = 0.f;

	// Steep parallax mapping
	do
	{
		prevMappedDepth = curMappedDepth;
		curMappedDepth = (1.f - texture(heightTex, curTexCoord).r);

		if (curLayerDepth > curMappedDepth)
			break;

		prevLayerDepth = curLayerDepth;
		prevTexCoord = curTexCoord;

		curLayerDepth += stepDepth;
		curTexCoord += stepOffset;
	}
	while (true);

	// Parallax occlusion mapping
	const float curDepthDelta	= (curMappedDepth - curLayerDepth);
	const float prevDepthDelta	= (prevMappedDepth - prevLayerDepth);
	const float weight			= (prevDepthDelta / (prevDepthDelta - curDepthDelta));

	return mix(prevTexCoord, curTexCoord, weight);
}

vec3 Material_getAmbient(const vec2 texCoord)
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
				retVal = texture(sampler2D(material.ambientTex), texCoord).rgb;
			else if (Material_isDiffuseTextureEnabled())
			{
				retVal = texture(sampler2D(material.diffuseTex), texCoord).rgb;
				retVal = Material_applyGamma(retVal);
			}
		}
	}

	return retVal;
}

vec3 Material_getDiffuse(const vec2 texCoord)
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
			retVal = texture(sampler2D(material.diffuseTex), texCoord).rgb;
			retVal = Material_applyGamma(retVal);
		}
	}

	return retVal;
}

vec3 Material_getSpecular(const vec2 texCoord)
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
				retVal = texture(sampler2D(material.specularTex), texCoord).rgb;

			else if (Material_isDiffuseTextureEnabled())
			{
				retVal = texture(sampler2D(material.diffuseTex), texCoord).rgb;
				retVal = Material_applyGamma(retVal);
			}
		}
	}

	return retVal;
}

vec3 Material_getEmissive(const vec2 texCoord)
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
			retVal = texture(sampler2D(material.emissiveTex), texCoord).rgb;
			retVal = Material_applyGamma(retVal);
		}
	}

	return retVal;
}

float Material_getShininess(const vec2 texCoord)
{
	if (Material_isShininessTextureEnabled())
		return texture(sampler2D(material.shininessTex), texCoord).r;

	return material.shininess;
}

float Material_getAlpha(const vec2 texCoord)
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
					retVal = texture(sampler2D(material.alphaTex), texCoord).r;

				else if (Material_isDiffuseTextureEnabled())
					retVal = texture(sampler2D(material.diffuseTex), texCoord).a;
			}
	}

	return retVal;
}

vec3 Material_getNormal(const vec2 texCoord, const vec3 targetNormal, const mat3 TBN)
{
	if (Material_isNormalTextureEnabled() && Material_isVertexTangentEnabled())
	{
		const vec3 fetched = texture(sampler2D(material.normalTex), texCoord).xyz;
		const vec3 tangentSpaceNormal = ((fetched * 2.f) - 1.f);

		return normalize(TBN * tangentSpaceNormal);
	}

	return targetNormal;
}

float Material_getLinearDepth(float fragDepth)
{
	const float ndcDepth = ((fragDepth * 2.f) - 1.f);
	const float linearDepth = (
		(2.f * material.zNear * material.zFar) /
		((material.zNear + material.zFar) + (ndcDepth * (material.zNear - material.zFar))));

	return (linearDepth / material.zFar);
}

vec4 Material_getEnvReflection(const vec3 targetNormal, const vec3 viewDirection, const vec2 texCoord)
{
	vec3 reflection = reflect(viewDirection, targetNormal);

	vec4 retVal = texture(samplerCube(material.environmentTex), reflection);

	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

vec4 Material_getEnvRefraction(const vec3 targetNormal, const vec3 viewDirection, const vec2 texCoord)
{
	vec3 refraction = refract(viewDirection, targetNormal, 1.f / 1.52f);

	vec4 retVal = texture(samplerCube(material.environmentTex), refraction);
	retVal.rgb = Material_applyGamma(retVal.rgb);
	return retVal;
}

#endif