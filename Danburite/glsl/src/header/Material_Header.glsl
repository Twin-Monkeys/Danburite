//? #version 460 core

#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

layout (std140, binding = BINDING_POINT_MATERIAL) uniform UBMaterial
{
	// 16byte
	layout(offset = 0) vec4 diffuseColor;

	// 8byte
	layout(offset = 16) uvec2 ambientTex;
	layout(offset = 24) uvec2 diffuseTex;
	layout(offset = 32) uvec2 specularTex;
	layout(offset = 40) uvec2 emissiveTex;
	layout(offset = 48) uvec2 shininessTex;
	layout(offset = 56) uvec2 alphaTex;
	layout(offset = 64) uvec2 normalTex;
	layout(offset = 72) uvec2 heightTex;
	layout(offset = 80) uvec2 environmentTex;

	// 4byte
	layout(offset = 88) uint type;
	layout(offset = 92) uint optionFlag;
	layout(offset = 96) uint vertexFlag;
	layout(offset = 100) float gamma;
	layout(offset = 104) float emissiveStrength;
	layout(offset = 108) float shininess;
	layout(offset = 112) float overriddenAlpha;
}
material;

bool Material_isLightingEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_LIGHTING) != 0);
}

bool Material_isTranslucencyEnabled()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_TRANSLUCENCY) != 0);
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

bool Material_isAlphaOverriding()
{
	return ((material.optionFlag & MATERIAL_OPTION_FLAG_ALPHA_OVERRIDING) != 0);
}

bool Material_isVertexPositionEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_POS) != 0);
}

bool Material_isVertexColorEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_COLOR) != 0);
}

bool Material_isVertexNormalEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_NORMAL) != 0);
}

bool Material_isVertexTexCoordEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_TEXCOORD) != 0);
}

bool Material_isVertexTangentEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_TANGENT) != 0);
}

bool Material_isVertexBoneEnabled()
{
	return ((material.vertexFlag & MATERIAL_VERTEX_FLAG_BONE) != 0);
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

vec3 Material_getDiffuse(const vec2 texCoord);

vec3 Material_getAmbient(const vec2 texCoord)
{
	if (Material_isAmbientTextureEnabled())
	{
		const vec3 retVal = texture(sampler2D(material.ambientTex), texCoord).rgb;
		return Material_applyGamma(retVal);
	}
	else
		return Material_getDiffuse(texCoord);
}

vec3 Material_getDiffuse(const vec2 texCoord)
{
	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.rgb;

	else if (!Material_isDiffuseTextureEnabled())
		return vec3(1.f, 1.f, 1.f);

	else
	{
		const vec3 retVal = texture(sampler2D(material.diffuseTex), texCoord).rgb;
		return Material_applyGamma(retVal);
	}
}

vec3 Material_getSpecular(const vec2 texCoord)
{
	if (Material_isSpecularTextureEnabled())
	{
		const vec3 retVal = texture(sampler2D(material.specularTex), texCoord).rgb;
		return Material_applyGamma(retVal);
	}
	else
		return Material_getDiffuse(texCoord);
}

vec3 Material_getEmissive(const vec2 texCoord)
{
	if (!Material_isEmissiveTextureEnabled())
		return vec3(0.f);

	const vec3 retVal = (texture(sampler2D(material.emissiveTex), texCoord).rgb * material.emissiveStrength);
	return Material_applyGamma(retVal);
}

float Material_getShininess(const vec2 texCoord)
{
	if (Material_isShininessTextureEnabled())
		return texture(sampler2D(material.shininessTex), texCoord).r;

	return material.shininess;
}

float Material_getAlpha(const vec2 texCoord)
{
	if (Material_isAlphaOverriding())
		return material.overriddenAlpha;

	if (Material_isAlphaTextureEnabled())
		return texture(sampler2D(material.alphaTex), texCoord).r;

	if (material.type == MATERIAL_TYPE_MONO_COLOR)
		return material.diffuseColor.a;
		
	else if (Material_isDiffuseTextureEnabled())
		return texture(sampler2D(material.diffuseTex), texCoord).a;
		
	else
		return 1.f;
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