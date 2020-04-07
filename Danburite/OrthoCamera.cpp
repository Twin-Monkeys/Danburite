#include "OrthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Danburite
{
	void OrthoCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		const float yTop	= (__orthoHeight * .5f);
		const float yBottom = -yTop;

		const float xRight	= (yTop * __aspectRatio);
		const float xLeft	= -xRight;

		projMatrix = ortho(xLeft, xRight, yBottom, yTop, __zNear, __zFar);
	}
}