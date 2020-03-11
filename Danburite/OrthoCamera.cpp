#include "OrthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Danburite
{
	void OrthoCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = ortho(__xOrthoLeft, __xOrthoRight, __yOrthoBottom, __yOrthoTop, __zOrthoNear, __zOrthoFar);
	}
}