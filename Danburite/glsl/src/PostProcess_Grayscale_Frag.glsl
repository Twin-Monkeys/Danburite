#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/Grayscale_Header.glsl"
 
out vec3 fragColor;

void main()
{
	const sampler2DRect srcTex = TextureContainer_getTextureAs2DRect(0);

	fragColor = texelFetch(srcTex, ivec2(gl_FragCoord.xy)).rgb;
	fragColor = vec3(Grayscale_getGrayscaledColor(fragColor));
} 