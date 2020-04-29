#pragma once

#include <glm/gtc/quaternion.hpp>

namespace Danburite
{
	class Quaternion
	{
	private:
		glm::quat __quaternion { 1.f, 0.f, 0.f, 0.f };

	protected:
		constexpr Quaternion(const glm::quat &src) noexcept;

	public:
		Quaternion() = default;
		Quaternion(const Quaternion &src) = default;

		explicit Quaternion(const glm::vec3 &eulerAngles) noexcept;
		Quaternion(const float pitch, const float yaw, const float roll) noexcept;
		Quaternion(const float angle, const glm::vec3 &axis) noexcept;
		Quaternion(const glm::mat3 &rotationMatrix) noexcept;
		Quaternion(const glm::mat4 &rotationMatrix) noexcept;

		Quaternion &set(const glm::vec3 &eulerAngles) noexcept;
		Quaternion &set(const float pitch, const float yaw, const float roll) noexcept;
		Quaternion &set(const float angle, const glm::vec3 &axis) noexcept;
		Quaternion &set(const glm::mat3 &rotationMatrix) noexcept;
		Quaternion &set(const glm::mat4 &rotationMatrix) noexcept;
		Quaternion &lookAt(const glm::vec3 &forward, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		Quaternion &rotateGlobal(const glm::vec3 &eularAngles) noexcept;
		Quaternion &rotateGlobal(const float pitch, const float yaw, const float roll) noexcept;
		Quaternion &rotateGlobal(const float angle, const glm::vec3 &axis) noexcept;

		Quaternion &rotateLocal(const glm::vec3 &eulerAngles) noexcept;
		Quaternion &rotateLocal(const float pitch, const float yaw, const float roll) noexcept;

		Quaternion &rotateFPS(const float pitch, const float yaw, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		glm::vec3 getEularAngles() const noexcept;
		void getEularAngles(glm::vec3 &retVal) const noexcept;

		glm::mat4 getMatrix() const noexcept;

		friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) noexcept;
		static Quaternion slerp(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept;
	};

	constexpr Quaternion::Quaternion(const glm::quat &src) noexcept :
		__quaternion(src)
	{}
}
