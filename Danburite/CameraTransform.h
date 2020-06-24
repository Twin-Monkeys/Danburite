#pragma once

#include "Transform.h"

namespace Danburite
{
	class CameraTransform : public Transform
	{
	private:
		glm::mat4 __viewMat { 1.f };

	public:
		constexpr const glm::mat4 &getViewMatrix() const noexcept;
		virtual void updateMatrix() noexcept;

		virtual ~CameraTransform() = default;
	};

	constexpr const glm::mat4 &CameraTransform::getViewMatrix() const noexcept
	{
		return __viewMat;
	}
}