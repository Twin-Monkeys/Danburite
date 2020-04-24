#pragma once

#include <glm/gtc/quaternion.hpp>

namespace Danburite
{
	class Quaternion
	{
	private:
		glm::quat __quaternion { 1.f, 0.f, 0.f, 0.f };

	public:
		Quaternion() = default;

		glm::vec3 getEularAngles() const noexcept;
		Quaternion &setRotation(const glm::vec3 &eularAngles) noexcept;
		Quaternion &setRotation(const float pitch, const float yaw, const float roll) noexcept;

		Quaternion &adjustRotation(const glm::vec3 &eularAngles) noexcept;
		Quaternion &adjustRotation(const float pitch, const float yaw, const float roll) noexcept;

		Quaternion &rotate(const float angle, const glm::vec3 &axis) noexcept;
		Quaternion &rotate(const glm::quat &quaternion) noexcept;

		glm::mat4 getMatrix() const noexcept;
		void getMatrix(glm::mat4 &retVal) const noexcept;
	};
}
