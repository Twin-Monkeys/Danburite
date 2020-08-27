//? #version 460 core

#ifndef __TEX_CONTAINER_HEADER__
#define __TEX_CONTAINER_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_TEX_CONTAINER) uniform UBTextureContainer
{
	layout(offset = 0) uvec2 textures[MAX_TEXTURE_CONTAINER_ELEMS];
}
textureContainer;

sampler2D TextureContainer_getTextureAs2D(const uint idx)
{
	return sampler2D(textureContainer.textures[idx]);
}

sampler2DRect TextureContainer_getTextureAs2DRect(const uint idx)
{
	return sampler2DRect(textureContainer.textures[idx]);
}

sampler2DMS TextureContainer_getTextureAs2DMS(const uint idx)
{
	return sampler2DMS(textureContainer.textures[idx]);
}

#endif