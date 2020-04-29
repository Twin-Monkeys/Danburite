#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Danburite
{
	void PerspectiveCamera::_onUpdateProjMatrix(const float deltaTime, mat4 &projMatrix) noexcept
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}
}