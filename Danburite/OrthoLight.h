#pragma once

#include "Light.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class OrthoLight abstract : public Light
	{
	private:
		OrthoCamera __camera;

	public:
		OrthoLight(ObjectGL::UniformSetter &uniformSetter, const LightType type);

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