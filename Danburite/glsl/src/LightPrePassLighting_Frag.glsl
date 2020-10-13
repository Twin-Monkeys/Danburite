#version 460 core

#include "header/Light_Header.glsl"
#include "header/Camera_Header.glsl"
#include "header/LightPrePass_Header.glsl"
#include "header/TextureContainer_Header.glsl"
 
layout (location = 0) out vec3 ambient;
layout (location = 1) out vec3 diffuse;
layout (location = 2) out vec3 specular;

void main()
{
	const ivec2 screenCoord = ivec2(gl_FragCoord.xy);
	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normal3_shininess1Tex = TextureContainer_getTextureAs2DRect(1);

	const uint curLightIdx = LightPrePass_getCurrentLightIdx();

	const vec3 worldSpaceTargetPos = texelFetch(posTex, screenCoord).xyz;
	const vec4 normal3_shininess1 = texelFetch(normal3_shininess1Tex, screenCoord);

	const vec3 worldSpaceTargetNormal = normal3_shininess1.xyz;
	const float shininess = normal3_shininess1.w;

	const float shadowOcclusion = Light_getShadowOcclusion(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal);
	const float shadowOcclusionInv = (1.f - shadowOcclusion);

	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - worldSpaceTargetPos);

	const float attenuation = Light_getAttenuation(curLightIdx, worldSpaceTargetPos);

	const vec3 lightAmbient = Light_getLightAmbient(curLightIdx, worldSpaceTargetPos);
	const vec3 lightDiffuse = Light_getLightDiffuse(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal);
	const vec3 lightSpecular = Light_getLightSpecular(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal, viewDir, shininess);

	ambient = (attenuation * lightAmbient);
	diffuse = ((shadowOcclusionInv * attenuation) * lightDiffuse);
	specular = ((shadowOcclusionInv * attenuation) * lightSpecular);

	if (LightPrePass_isSsaoEnabled())
	{
		const sampler2DRect ambientOcclusionInvTex = TextureContainer_getTextureAs2DRect(2);
		const float ambientOcclusionInv = texelFetch(ambientOcclusionInvTex, screenCoord).r;

		ambient *= ambientOcclusionInv;
		diffuse *= ambientOcclusionInv;
		specular *= ambientOcclusionInv;
	}
} 