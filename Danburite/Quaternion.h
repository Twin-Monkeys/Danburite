#pragma once

#include <glm/gtc/quaternion.hpp>
#include <utility>

namespace Danburite
{
	class Quaternion
	{
	private:
		glm::quat __quaternion { 1.f, 0.f, 0.f, 0.f };

	public:
		/* Ctors */

		Quaternion() = default;
		Quaternion(const Quaternion &src, const bool normalization = true) noexcept;

		// default
		Quaternion(const glm::quat &src, const bool normalization = true) noexcept;
		Quaternion(const float w, const float x, const float y, const float z, const bool normalization = true) noexcept;

		// euler angles
		explicit Quaternion(const glm::vec3 &eulerAngles) noexcept;
		Quaternion(const float pitch, const float yaw, const float roll) noexcept;

		// rodrigues
		Quaternion(const float angle, const glm::vec3 &axis) noexcept;

		// matrix
		Quaternion(const glm::mat3 &rotationMatrix, const bool normalization = true) noexcept;
		Quaternion(const glm::mat4 &rotationMatrix, const bool normalization = true) noexcept;


		/* Setters */

		// default
		Quaternion &set(const glm::quat &src, const bool normalization = true) noexcept;
		Quaternion &set(const float w, const float x, const float y, const float z, const bool normalization = true) noexcept;
		Quaternion &set(const Quaternion &src, const bool normalization = true) noexcept;

		// euler angles
		Quaternion &set(const glm::vec3 &eulerAngles) noexcept;
		Quaternion &set(const float pitch, const float yaw, const float roll) noexcept;

		// rodrigues
		Quaternion &set(const float angle, const glm::vec3 &axis) noexcept;

		// matrix
		Quaternion &set(const glm::mat3 &rotationMatrix, const bool normalization = true) noexcept;
		Quaternion &set(const glm::mat4 &rotationMatrix, const bool normalization = true) noexcept;


		/* Operations */

		Quaternion &orient(const glm::vec3 &forward, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		Quaternion &rotateGlobal(const glm::vec3 &eularAngles) noexcept;
		Quaternion &rotateGlobal(const float pitch, const float yaw, const float roll) noexcept;
		Quaternion &rotateGlobal(const float angle, const glm::vec3 &axis) noexcept;

		Quaternion &rotateLocal(const glm::vec3 &eulerAngles) noexcept;
		Quaternion &rotateLocal(const float pitch, const float yaw, const float roll) noexcept;

		Quaternion &rotateFPS(const float pitch, const float yaw, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;


		/* Getters */

		glm::vec3 getEularAngles() const noexcept;
		glm::mat4 getMatrix() const noexcept;

		Quaternion inverse() const noexcept;
		std::pair<float, glm::vec3> getAngleAxis() const noexcept;

		friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) noexcept;
		static Quaternion slerp(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept;
	};
}