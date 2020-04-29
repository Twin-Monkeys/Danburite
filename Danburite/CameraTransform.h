#pragma once

#include "AnimatableTransform.h"

namespace Danburite
{
	class CameraTransform : public AnimatableTransform
	{
	private:
		glm::mat4 __viewTranslationMat	{ 1.f };
		glm::mat4 __viewRotationMat		{ 1.f };
		glm::mat4 __viewMat				{ 1.f };

	protected:
		virtual void _onUpdateTranslationMatrix(glm::mat4 &translationMat) noexcept override;
		virtual void _onUpdateRotationMatrix(glm::mat4 &rotationMat) noexcept override;

	public:
		constexpr const glm::mat4 &getViewTranslationMatrix() const noexcept;
		constexpr const glm::mat4 &getViewRotationMatrix() const noexcept;
		constexpr const glm::mat4 &getViewMatrix() const noexcept;

		virtual void updateMatrix(const float deltaTime) noexcept;

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

	constexpr const glm::mat4 &CameraTransform::getViewMatrix() const noexcept
	{
		return __viewMat;
	}
}