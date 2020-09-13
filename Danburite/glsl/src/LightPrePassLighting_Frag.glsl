#version 460 core

#include "header/Light_Header.glsl"
#include "header/Camera_Header.glsl"
#include "header/LightPrePass_Header.glsl"
#include "header/TextureContainer_Header.glsl"
 
layout (location = 0) out vec3 ambient;
layout (location = 1) out vec3 diffuse;
layout (location = 2) out vec3 specular;
layout (location = 3) out float ambientOcclusion;

void main()
{
	// Light properties

	const uint curLightIdx = LightPrePass_getCurrentLightIdx();
	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normal3_shininess1Tex = TextureContainer_getTextureAs2DRect(1);

	const vec4 normal3_shininess1 = texelFetch(normal3_shininess1Tex, ivec2(gl_FragCoord.xy));

	const vec3 worldSpaceTargetPos = texelFetch(posTex, ivec2(gl_FragCoord.xy)).xyz;
	const vec3 worldSpaceTargetNormal = normal3_shininess1.xyz;
	const float attenuation = Light_getAttenuation(curLightIdx, worldSpaceTargetPos);

	const float shadowOcclusion = Light_getShadowOcclusion(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal);
	const float shadowOcclusionInv = (1.f - shadowOcclusion);

	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - worldSpaceTargetPos);
	const float shininess = normal3_shininess1.w;

	ambient = (attenuation * Light_getLightAmbient(curLightIdx, worldSpaceTargetPos));
	diffuse = (shadowOcclusionInv * attenuation * Light_getLightDiffuse(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal));
	specular = (shadowOcclusionInv * attenuation * Light_getLightSpecular(curLightIdx, worldSpaceTargetPos, worldSpaceTargetNormal, viewDir, shininess));


	// Ambient occlusion

	const vec3 viewSpaceTargetPos = (Camera_getViewMatrix() * vec4(worldSpaceTargetPos, 1.f)).xyz;

	// Assume a view matrix has no scaling factor.
	const vec3 viewSpaceTargetNormal = (Camera_getViewMatrix() * vec4(worldSpaceTargetNormal, 0.f)).xyz;


} 