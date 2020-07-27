//? #version 460 core

#ifndef __TEX_CONTAINER_HEADER__
#define __TEX_CONTAINER_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

struct TextureContainer
{
	uvec2 tex0;
	uvec2 tex1;
	uvec2 tex2;
	uvec2 tex3;
	uvec2 tex4;
	uvec2 tex5;
	uvec2 tex6;
	uvec2 tex7;
	uvec2 tex8;
	uvec2 tex9;
};

layout(binding = BINDING_POINT_TEX_CONTAINER) uniform UBTextureContainer
{
	TextureContainer textureContainer;
};

uvec2 TextureContainer_getHandle(const uint idx)
{
	if (idx == 0)
		return textureContainer.tex0;

	else if (idx == 1)
		return textureContainer.tex1;

	else if (idx == 2)
		return textureContainer.tex2;

	else if (idx == 3)
		return textureContainer.tex3;

	else if (idx == 4)
		return textureContainer.tex4;

	else if (idx == 5)
		return textureContainer.tex5;

	else if (idx == 6)
		return textureContainer.tex6;

	else if (idx == 7)
		return textureContainer.tex7;

	else if (idx == 8)
		return textureContainer.tex8;

	else if (idx == 9)
		return textureContainer.tex9;

	return uvec2(0U, 0U);
}

sampler2D TextureContainer_getTextureAs2D(const uint idx)
{
	return sampler2D(TextureContainer_getHandle(idx));
}

sampler2DRect TextureContainer_getTextureAs2DRect(const uint idx)
{
	return sampler2DRect(TextureContainer_getHandle(idx));
}

sampler2DMS TextureContainer_getTextureAs2DMS(const uint idx)
{
	return sampler2DMS(TextureContainer_getHandle(idx));
}

#endif