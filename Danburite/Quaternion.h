#pragma once

#include <glm/gtc/quaternion.hpp>
#include <utility>
#include "EulerAngleOrder.h"

namespace Danburite
{
	class Quaternion
	{
	private:
		glm::quat __quaternion { 1.f, 0.f, 0.f, 0.f };

	public:
		/* Ctors */

		Quaternion() = default;
		Quaternion(const Quaternion &src) noexcept;

		// default
		Quaternion(const glm::quat &src) noexcept;
		Quaternion(const float w, const float x, const float y, const float z) noexcept;

		// euler angles
		Quaternion(const glm::vec3 &eulerAngles, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;
		Quaternion(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;

		// rodrigues
		Quaternion(const float angle, const glm::vec3 &axis) noexcept;

		// matrix
		Quaternion(const glm::mat3 &rotationMatrix) noexcept;
		Quaternion(const glm::mat4 &rotationMatrix) noexcept;


		/* Setters */

		// default
		Quaternion &set(const glm::quat &src) noexcept;
		Quaternion &set(const float w, const float x, const float y, const float z) noexcept;
		Quaternion &set(const Quaternion &src) noexcept;

		// euler angles
		Quaternion &setFromPitch(const float pitch) noexcept;
		Quaternion &setFromYaw(const float yaw) noexcept;
		Quaternion &setFromRoll(const float roll) noexcept;
		Quaternion &set(const glm::vec3 &eulerAngles, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;
		Quaternion &set(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;

		// rodrigues
		Quaternion &set(const float angle, const glm::vec3 &axis) noexcept;

		// matrix
		Quaternion &set(const glm::mat3 &rotationMatrix) noexcept;
		Quaternion &set(const glm::mat4 &rotationMatrix) noexcept;


		/* Operations */

		Quaternion &orient(const glm::vec3 &forward, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		Quaternion &rotateGlobalPitch(const float pitch) noexcept;
		Quaternion &rotateGlobalYaw(const float yaw) noexcept;
		Quaternion &rotateGlobalRoll(const float roll) noexcept;
		Quaternion &rotateGlobal(const glm::vec3 &eularAngles, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;
		Quaternion &rotateGlobal(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;
		Quaternion &rotateGlobal(const float angle, const glm::vec3 &axis) noexcept;

		Quaternion &rotateLocalPitch(const float pitch) noexcept;
		Quaternion &rotateLocalYaw(const float yaw) noexcept;
		Quaternion &rotateLocalRoll(const float roll) noexcept;
		Quaternion &rotateLocal(const glm::vec3 &eulerAngles, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;
		Quaternion &rotateLocal(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder = EulerAngleOrder::PITCH_YAW_ROLL) noexcept;

		Quaternion &rotateFPSPitch(const float pitch, const glm::vec3& referenceUp = { 0.f, 1.f, 0.f }) noexcept;
		Quaternion &rotateFPSYaw(const float yaw, const glm::vec3& referenceUp = { 0.f, 1.f, 0.f }) noexcept;


		/* Etc */

		glm::vec3 getEularAngles() const noexcept;
		glm::mat4 getMatrix() const noexcept;

		Quaternion inverse() const noexcept;
		std::pair<float, glm::vec3> getAngleAxis() const noexcept;

		friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) noexcept;
		friend Quaternion operator-(const Quaternion &quat) noexcept;

		static Quaternion slerp(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept;
	};
}