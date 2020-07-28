#pragma once

#include "Camera.h"
#include "Transform.h"

namespace Danburite
{
	class TransformableCamera abstract : public Camera
	{
	private:
		Transform __transform;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept override;
		virtual void _onDeploy(ObjectGL::UniformSetter &cameraSetter) noexcept override;

	public:
		constexpr Transform &getTransform() noexcept;
		constexpr const Transform &getTransform() const noexcept;

		virtual ~TransformableCamera() = default;
	};

	constexpr Transform &TransformableCamera::getTransform() noexcept
	{
		return __transform;
	}

	constexpr const Transform &TransformableCamera::getTransform() const noexcept
	{
		return __transform;
	}
}
