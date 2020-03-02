#include "OrthoCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OrthoCamera::OrthoCamera() noexcept
	{
		updateProjMatrix();
	}

	void OrthoCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = lookAt(__pos, __pos + __forward, __up);
	}

	void OrthoCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = ortho(__xLeft, __xRight, __yBottom, __yTop, __zNear, __zFar);
	}

	void OrthoCamera::_onDeploy(UniformSetter &uniformSetter) noexcept
	{
		Camera::_onDeploy(uniformSetter);
		uniformSetter.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __pos);
	}

	void OrthoCamera::pitch(const float angle) noexcept
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

	void OrthoCamera::yaw(const float angle) noexcept
	{
		__forward = normalize(rotate(__forward, angle, __up));
		__horizontal = normalize(cross(__forward, __up));
	}
}