#include "PerspectiveCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PerspectiveCamera::PerspectiveCamera() noexcept
	{
		updateProjMatrix();
	}

	void PerspectiveCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = lookAt(__pos, __pos + __forward, __up);
	}

	void PerspectiveCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}

	void PerspectiveCamera::_onDeploy(UniformSetter &target) noexcept
	{
		Camera::_onDeploy(target);
		target.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __pos);
	}

	void PerspectiveCamera::pitch(const float angle) noexcept
	{
		float newPitch = (__pitch + angle);
		float validAngle = angle;

		if (newPitch > __maxPitch)
		{
			validAngle -= (newPitch - __maxPitch);
			newPitch = __maxPitch;
		}
		else if (newPitch < -__maxPitch)
		{
			validAngle -= (newPitch + __maxPitch);
			newPitch = -__maxPitch;
		}

		__pitch = newPitch;
		__forward = normalize(rotate(__forward, validAngle, __horizontal));
		__vertical = normalize(cross(__horizontal, __forward));
	}

	void PerspectiveCamera::yaw(const float angle) noexcept
	{
		__forward = normalize(rotate(__forward, angle, __up));
		__horizontal = normalize(cross(__forward, __up));
	}
}