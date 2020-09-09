#pragma once

#include "PointLight.h"
#include "SpotLightComponent.h"

namespace Danburite
{
	class SpotLight : public PointLight, public SpotLightComponent
	{
	protected:
		virtual void _onDeploy(LightUniformInterface &lightUI) noexcept override;

	public:
		SpotLight(const GLuint index);
		virtual ~SpotLight() = default;
	};
}