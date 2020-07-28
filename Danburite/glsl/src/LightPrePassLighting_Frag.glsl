#version 460 core

#include "header/TextureContainer_Header.glsl"
 
layout (location = 0) out vec4 ambient3_attenuation1;
layout (location = 1) out vec4 diffuse3_occlusionInv1;
layout (location = 2) out vec3 specular;

void main()
{
	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normal3_shininess1Tex = TextureContainer_getTextureAs2DRect(1);

	ambient3_attenuation1 = texture(normal3_shininess1Tex, gl_FragCoord.xy);
	diffuse3_occlusionInv1 = vec4(0.f);
	specular = vec3(0.f);
} 