#pragma once

#include "Transform.h"

namespace Danburite
{
	class CameraTransform : public Transform
	{
	private:
		mutable glm::mat4 __viewTranslationMat	{ 1.f };
		mutable glm::mat4 __viewRotationMat		{ 1.f };
		mutable glm::mat4 __viewMat				{ 1.f };

	protected:
		virtual void _onValidateTranslation(glm::mat4 &translationMat) const noexcept override;
		virtual void _onValidateRotation(glm::mat4 &rotationMat) const noexcept override;

	public:
		const glm::mat4 &getViewTranslationMatrix() const noexcept;
		const glm::mat4 &getViewRotationMatrix() const noexcept;
		const glm::mat4 &getViewMatrix() const noexcept;

		virtual ~CameraTransform() = default;
	};
}