#pragma once

#include "PointLight.h"
#include "DirectionalLightComponent.h"
#include "SpotLightComponent.h"

namespace Danburite
{
	class SpotLight :
		public PointLight, public DirectionalLightComponent, public SpotLightComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		SpotLight(ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual void bakeDepthMap() noexcept override;

		virtual ~SpotLight() = default;
	};
}