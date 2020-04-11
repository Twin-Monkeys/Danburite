#pragma once

#include "PerspectiveLight.h"
#include "LightBaseComponent.h"
#include "AttenuatedLightComponent.h"

namespace Danburite
{
	class PointLight :
		public PerspectiveLight, public LightBaseComponent, public AttenuatedLightComponent
	{
	protected:
		PointLight(const LightType type);

		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		PointLight();

		virtual ~PointLight() = default;
	};
}