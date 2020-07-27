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

		void __setValidDistance() noexcept;

	protected:
		PointLight(const LightType type);

		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		PointLight();
		void setLuminanceTolerance(const float tolerance) noexcept;

		using LightBaseComponent::setAlbedo;
		virtual void setAlbedo(const glm::vec3 &albedo) noexcept;

		virtual void setAmbientStrength(const float strength) noexcept;
		virtual void setDiffuseStrength(const float strength) noexcept;
		virtual void setSpecularStrength(const float strength) noexcept;

		virtual void setAttenuation(const float constant, const float linear, const float quadratic) noexcept override;

		virtual void volumeDrawcall() noexcept override;

		virtual ~PointLight() = default;
	};
}