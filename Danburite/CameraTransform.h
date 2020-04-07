#pragma once

#include "Transform.h"

namespace Danburite
{
	class CameraTransform : public Transform
	{
	private:
		glm::mat4 __viewTranslationMat	{ 1.f };
		glm::mat4 __viewRotationMat		{ 1.f };

	protected:
		virtual void _onUpdateRotation(glm::mat4 &rotationMat) const noexcept override;

	public:
		constexpr const glm::mat4 &getViewTranslationMatrix() const noexcept;
		constexpr const glm::mat4 &getViewRotationMatrix() const noexcept;

		virtual void update() noexcept override;

		virtual ~CameraTransform() = default;
	};

	constexpr const glm::mat4 &CameraTransform::getViewTranslationMatrix() const noexcept
	{
		return __viewTranslationMat;
	}

	constexpr const glm::mat4 &CameraTransform::getViewRotationMatrix() const noexcept
	{
		return __viewRotationMat;
	}
}