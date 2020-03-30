#pragma once

#include "Light.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class TransformableCameraLight abstract : public Light, public Updatable
	{
	protected:
		virtual TransformableCamera &_getCamera() noexcept = 0;
		virtual const TransformableCamera &_getCamera() const noexcept = 0;

		virtual const glm::mat4 &_getViewMatrix() const noexcept override;
		virtual const glm::mat4 &_getProjMatrix() const noexcept override;

		void _deployDirection(LightUniformSetter &lightParamSetter) noexcept;
		void _deployPosition(LightUniformSetter &lightParamSetter) noexcept;

	public:
		TransformableCameraLight(const LightType type);

		CameraTransform &getTransform() noexcept;
		const CameraTransform &getTransform() const noexcept;

		virtual void update() noexcept override;
	};
}