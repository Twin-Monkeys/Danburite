#pragma once

#include "PointLight.h"
#include "SpotLightComponent.h"

namespace Danburite
{
	class SpotLight : public PointLight, public SpotLightComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		SpotLight();
		virtual void volumeDrawcall() noexcept override;

		virtual ~SpotLight() = default;
	};
}