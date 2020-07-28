#version 460 core

#include "header/LightPrePass_Header.glsl"
#include "header/TextureContainer_Header.glsl"
#include "header/Light_Header.glsl"
#include "header/Camera_Header.glsl"
 
layout (location = 0) out vec4 ambient3_attenuation1;
layout (location = 1) out vec4 diffuse3_occlusionInv1;
layout (location = 2) out vec3 specular;

void main()
{
	const uint curLightIdx = LightPrePass_getCurrentLightIdx();
	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normal3_shininess1Tex = TextureContainer_getTextureAs2DRect(1);

	const vec4 normal3_shininess1 = texture(normal3_shininess1Tex, gl_FragCoord.xy);

	const vec3 targetPos = texture(posTex, gl_FragCoord.xy).xyz;
	const vec3 targetNormal = normal3_shininess1.xyz;
	const float shininess = normal3_shininess1.w;

	const vec3 ambient = Light_getLightAmbient(curLightIdx, targetPos);
	const float attenuation = Light_getAttenuation(curLightIdx, targetPos);
	ambient3_attenuation1 = vec4(ambient, attenuation);

	const vec3 diffuse = Light_getLightDiffuse(curLightIdx, targetPos, targetNormal);
	const float occlusion = Light_getOcclusion(curLightIdx, targetPos, targetNormal);
	const float occlusionInv = (1.f - occlusion);
	diffuse3_occlusionInv1 = vec4(diffuse, occlusionInv);

	const vec3 viewPos = Camera_getPosition();
	const vec3 viewDir = normalize(viewPos - targetPos);
	specular = Light_getLightSpecular(curLightIdx, targetPos, targetNormal, viewDir, shininess);
} 