#version 460 core

#include "header/TextureContainer_Header.glsl"
 
out vec4 outColor;

void main()
{
	const sampler2DRect accumulationTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect revealageTex = TextureContainer_getTextureAs2DRect(1);

	const vec4 accumulation = texture(accumulationTex, gl_FragCoord.xy);
	const float revealage = texture(revealageTex, gl_FragCoord.xy).r;

	/*
		accum alpha가 0이면 revealage는 항상 1이므로
		이에 대한 예외처리를 추가할 필요는 없음.
	*/
	if (accumulation.a < EPSILON)
		discard;

	outColor.rgb = (accumulation.rgb / accumulation.a);

	
	/*
		revealage가 완전 0인 경우에도 약간의 투명 효과를 부여햐여
		사용자가 어색함을 느끼지 않도록 한다.
	*/
	outColor.a = min(.999f, 1.f - revealage);
} 