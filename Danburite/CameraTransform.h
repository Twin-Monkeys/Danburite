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
		virtual void _onUpdateTranslationMatrix(glm::mat4 &translationMat) noexcept override;
		virtual void _onUpdateRotationMatrix(glm::mat4 &rotationMat) noexcept override;

	public:
		constexpr const glm::mat4 &getViewTranslationMatrix() const noexcept;
		constexpr const glm::mat4 &getViewRotationMatrix() const noexcept;

		glm::mat4 getViewMatrix() const noexcept;
		void getViewMatrix(glm::mat4 &retVal) const noexcept;

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