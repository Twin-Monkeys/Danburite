#pragma once

#include "PerspectiveCameraLight.h"
#include "LightBaseComponent.h"
#include "AttenuatedLightComponent.h"

namespace Danburite
{
	class PointLight :
		public PerspectiveCameraLight, public LightBaseComponent, public AttenuatedLightComponent
	{
	protected:
		PointLight(const LightType type);

		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		PointLight();

		virtual ~PointLight() = default;
	};
}