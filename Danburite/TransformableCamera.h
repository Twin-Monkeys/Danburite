#pragma once

#include "Camera.h"
#include "CameraTransform.h"

namespace Danburite
{
	class TransformableCamera abstract : public Camera
	{
	private:
		CameraTransform __transform;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4& viewMatrix) noexcept override;
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) const noexcept override;

	public:
		constexpr CameraTransform &getTransform() noexcept;
		constexpr const CameraTransform &getTransform() const noexcept;

		virtual void update() noexcept override;

		virtual ~TransformableCamera() = default;
	};

	constexpr CameraTransform &TransformableCamera::getTransform() noexcept
	{
		return __transform;
	}

	constexpr const CameraTransform &TransformableCamera::getTransform() const noexcept
	{
		return __transform;
	}
}
