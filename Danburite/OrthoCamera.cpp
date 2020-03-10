#include "OrthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Danburite
{
	void OrthoCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = ortho(__xLeft, __xRight, __yBottom, __yTop, __zNear, __zFar);
	}
}