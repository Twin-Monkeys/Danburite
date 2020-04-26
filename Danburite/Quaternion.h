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
		void getEularAngles(glm::vec3 &retVal) const noexcept;

		Quaternion &set(const glm::vec3 &eularAngles) noexcept;
		Quaternion &set(const float pitch, const float yaw, const float roll) noexcept;

		Quaternion &rotate(const glm::vec3 &eularAngles) noexcept;
		Quaternion &rotate(const float pitch, const float yaw, const float roll) noexcept;
		Quaternion &rotate(const float angle, const glm::vec3 &axis) noexcept;

		Quaternion &adjustFPSPitch(const float pitch, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;
		Quaternion &adjustFPSYaw(const float yaw, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		glm::mat4 getMatrix() const noexcept;
		void getMatrix(glm::mat4 &retVal) const noexcept;
	};
}
