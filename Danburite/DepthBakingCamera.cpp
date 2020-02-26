#include "DepthBakingCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void DepthBakingCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = lookAt(__pos, __pos + __direction, __up);
	}

	void DepthBakingCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = ortho(
			__viewingVolumeLeft, __viewingVolumeRight,
			__viewingVolumeBottom, __viewingVolumeTop,
			__viewingVolumeNear, __viewingVolumeFar);
	}

	void DepthBakingCamera::setDirection(const vec3 &direction) noexcept
	{
		__direction = normalize(direction);
	}

	void DepthBakingCamera::setDirection(const float x, const float y, const float z) noexcept
	{
		setDirection({ x, y, z });
	}

	void DepthBakingCamera::setUp(const vec3 &up) noexcept
	{
		__up = normalize(up);
	}

	void DepthBakingCamera::setUp(const float x, const float y, const float z) noexcept
	{
		setUp({ x, y, z });
	}
}