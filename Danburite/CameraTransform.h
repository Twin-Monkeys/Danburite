#pragma once

#include "Transform.h"

namespace Danburite
{
	class CameraTransform : public Transform
	{
	private:
		mutable glm::mat4 __viewTranslationMat	{ 1.f };
		mutable glm::mat4 __viewRotationMat		{ 1.f };
		mutable glm::mat4 __viewRotationInvMat	{ 1.f };
		mutable glm::mat4 __viewMat				{ 1.f };

	protected:
		virtual void _onValidateTranslation() const noexcept override;
		virtual void _onValidateRotation() const noexcept override;

	public:
		virtual const glm::vec4 &getForward() const noexcept override;
		virtual const glm::vec4 &getHorizontal() const noexcept override;
		virtual const glm::vec4 &getVertical() const noexcept override;

		const glm::mat4 &getViewTranslationMatrix() const noexcept;
		const glm::mat4 &getViewRotationMatrix() const noexcept;
		const glm::mat4 &getViewRotationInvMatrix() const noexcept;
		const glm::mat4 &getViewMatrix() const noexcept;

		virtual ~CameraTransform() = default;
	};
}