#pragma once

#include "PerspectiveLight.h"
#include "LightBaseComponent.h"
#include "AttenuatedLightComponent.h"

namespace Danburite
{
	class PointLight :
		public PerspectiveLight, public LightBaseComponent, public AttenuatedLightComponent
	{
	private:
		float __luminanceTolerance =
			Constant::Light::AttenuatedComponent::LUMINANCE_TOLERANCE;

	protected:
		PointLight(const LightType type);

		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		PointLight();
		constexpr void setLuminanceTolerance(const float tolerance) noexcept;

		virtual ~PointLight() = default;
	};

	constexpr void PointLight::setLuminanceTolerance(const float tolerance) noexcept
	{
		__luminanceTolerance = tolerance;
	}
}