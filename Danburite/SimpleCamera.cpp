#include "SimpleCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SimpleCamera::SimpleCamera() noexcept
	{
		updateProjMatrix();
	}

	void SimpleCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = lookAt(__pos, __pos + __forward, __up);
	}

	void SimpleCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}

	void SimpleCamera::_onDeploy(UniformSetter &target) noexcept
	{
		Camera::_onDeploy(target);
		target.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __pos);
	}

	const vec3 &SimpleCamera::getPosition() const noexcept
	{
		return __pos;
	}

	const vec3& SimpleCamera::getForward() const noexcept
	{
		return __forward;
	}

	const vec3& SimpleCamera::getHorizontal() const noexcept
	{
		return __horizontal;
	}

	const vec3& SimpleCamera::getVertical() const noexcept
	{
		return __vertical;
	}

	void SimpleCamera::setPosition(const vec3 &position) noexcept
	{
		__pos = position;
	}

	void SimpleCamera::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	void SimpleCamera::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	void SimpleCamera::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	void SimpleCamera::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	void SimpleCamera::adjustPosition(const vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	void SimpleCamera::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	void SimpleCamera::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	void SimpleCamera::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	void SimpleCamera::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}

	void SimpleCamera::moveForward(const float delta) noexcept
	{
		adjustPosition(__forward * delta);
	}

	void SimpleCamera::moveHorizontal(const float delta) noexcept
	{
		adjustPosition(__horizontal * delta);
	}

	void SimpleCamera::moveVertical(const float delta) noexcept
	{
		adjustPosition(__vertical * delta);
	}

	void SimpleCamera::pitch(const float angle) noexcept
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

	void SimpleCamera::yaw(const float angle) noexcept
	{
		__forward = normalize(rotate(__forward, angle, __up));
		__horizontal = normalize(cross(__forward, __up));
	}

	void SimpleCamera::setFov(const float fov) noexcept
	{
		float validFov = fov;

		if (validFov > __maxFov)
			validFov = __maxFov;
		else if (validFov < __minFov)
			validFov = __minFov;

		__fov = validFov;
	}

	void SimpleCamera::resetFov() noexcept
	{
		setFov(Constant::Camera::FOV);
	}

	void SimpleCamera::adjustFov(const float delta) noexcept
	{
		setFov(__fov + delta);
	}

	void SimpleCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	void SimpleCamera::setAspectRatio(const int width, const int height) noexcept
	{
		setAspectRatio(float(width) / float(height));
	}

	void SimpleCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	void SimpleCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}

	void SimpleCamera::setMaxPitch(const float maxPitch) noexcept
	{
		__maxPitch = maxPitch;
	}

	void SimpleCamera::setMaxFov(const float maxFov) noexcept
	{
		__maxFov = maxFov;
	}

	void SimpleCamera::setMinFov(const float minFov) noexcept
	{
		__minFov = minFov;
	}
}