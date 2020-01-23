#pragma once

#include <GL/glew.h>

namespace Danburite
{
	enum class LightType : GLenum
	{
		DIRECTIONAL = 0,
		POINT,
		SPOT
	};
}
