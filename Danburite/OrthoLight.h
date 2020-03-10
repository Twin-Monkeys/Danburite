#pragma once

#include "Light.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class OrthoLight abstract : public Light
	{
	private:
		OrthoCamera __camera;

	protected:
		virtual const glm::mat4 &_getViewMatrix() const noexcept override;
		virtual const glm::mat4 &_getProjMatrix() const noexcept override;

	public:
		OrthoLight(
			const LightType type,
			ObjectGL::UniformSetter& lightParamSetter,
			ObjectGL::UniformSetter& cameraParamSetter);

		constexpr CameraTransform &getTransform() noexcept;
		constexpr const CameraTransform &getTransform() const noexcept;
	};

	constexpr CameraTransform &OrthoLight::getTransform() noexcept
	{
		return __camera.getTransform();
	}

	constexpr const CameraTransform &OrthoLight::getTransform() const noexcept
	{
		return __camera.getTransform();
	}
}