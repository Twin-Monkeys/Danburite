#pragma once

#include "Light.h"
#include "PerspectiveCamera.h"

namespace Danburite
{
	class PerspectiveLight abstract : public Light
	{
	private:
		PerspectiveCamera __camera;

	public:
		PerspectiveLight(ObjectGL::UniformSetter &uniformSetter, const LightType type);

		constexpr PerspectiveCamera &getCamera() noexcept;
		constexpr const PerspectiveCamera &getCamera() const noexcept;
	};

	constexpr PerspectiveCamera &PerspectiveLight::getCamera() noexcept
	{
		return __camera;
	}

	constexpr const PerspectiveCamera &PerspectiveLight::getCamera() const noexcept
	{
		return __camera;
	}
}