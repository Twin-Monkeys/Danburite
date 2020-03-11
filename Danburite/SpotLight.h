#pragma once

#include "PointLight.h"
#include "SpotLightComponent.h"

namespace Danburite
{
	class SpotLight : public PointLight, public SpotLightComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &lightParamSetter) noexcept override;

	public:
		SpotLight(ObjectGL::UniformSetter &lightParamSetter, ObjectGL::UniformSetter &cameraParamSetter) noexcept;

		virtual ~SpotLight() = default;
	};
}