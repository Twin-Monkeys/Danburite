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
	const uint curLightIdx = LightPrePass_getCurrentLightIdx();
	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normal3_shininess1Tex = TextureContainer_getTextureAs2DRect(1);

	const vec4 normal3_shininess1 = texture(normal3_shininess1Tex, gl_FragCoord.xy);

	const vec3 targetPos = texture(posTex, gl_FragCoord.xy).xyz;
	const vec3 targetNormal = normal3_shininess1.xyz;
	const float attenuation = Light_getAttenuation(curLightIdx, targetPos);

	const float occlusion = Light_getOcclusion(curLightIdx, targetPos, targetNormal);
	const float occlusionInv = (1.f - occlusion);

	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - targetPos);
	const float shininess = normal3_shininess1.w;

	ambient = (attenuation * Light_getLightAmbient(curLightIdx, targetPos));
	diffuse = (occlusionInv * attenuation * Light_getLightDiffuse(curLightIdx, targetPos, targetNormal));
	specular = (occlusionInv * attenuation * Light_getLightSpecular(curLightIdx, targetPos, targetNormal, viewDir, shininess));
} 