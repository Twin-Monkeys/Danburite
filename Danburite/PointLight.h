#pragma once

#include "PerspectiveLight.h"
#include "LightBaseComponent.h"
#include "AttenuatedLightComponent.h"
#include "SceneObject.h"

namespace Danburite
{
	class PointLight :
		public PerspectiveLight, public LightBaseComponent, public AttenuatedLightComponent
	{
	private:
		float __luminanceTolerance =
			Constant::Light::AttenuatedComponent::LUMINANCE_TOLERANCE;

		std::shared_ptr<Danburite::SceneObject> __pVolume = std::make_shared<SceneObject>();

		void __setValidDistance() noexcept;

	protected:
		PointLight(const LightType type, const GLuint index);

		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;
		virtual void _onVolumeDrawcall() noexcept override;

	public:
		PointLight(const GLuint index);
		void setLuminanceTolerance(const float tolerance) noexcept;

		using LightBaseComponent::setAlbedo;
		virtual void setAlbedo(const glm::vec3 &albedo) noexcept;

		virtual void setAmbientStrength(const float strength) noexcept;
		virtual void setDiffuseStrength(const float strength) noexcept;
		virtual void setSpecularStrength(const float strength) noexcept;

		virtual void setAttenuation(const float constant, const float linear, const float quadratic) noexcept override;

		virtual void update(const float delta) noexcept override;

		virtual ~PointLight() = default;
	};
}