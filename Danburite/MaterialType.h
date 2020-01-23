#pragma once

#include <gl/glew.h>

namespace Danburite
{
	enum class MaterialType : GLuint
	{
		MONO_COLOR = 0,
		PHONG,
		SILHOUETTE,
		OUTLINING_PHONG,
		TRANSPARENT_PHONG,
		REFLECTION,
		REFLECTION_PHONG,
		REFRACTION,
		EXPLODING_PHONG
	};
}