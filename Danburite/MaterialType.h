#pragma once

#include <gl/glew.h>

namespace Danburite
{
	enum class MaterialType : GLuint
	{
		MONO_COLOR = 0,
		PHONG,
		REFLECTION,
		REFRACTION,
		RAW_DRAWCALL
	};
}