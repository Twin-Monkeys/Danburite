#pragma once

#include "Light.h"
#include "LightBaseComponent.h"
#include "PositionableLightComponent.h"
#include "AttenuatedLightComponent.h"

namespace Danburite
{
	class PointLight :
		public Light, public LightBaseComponent, public PositionableLightComponent, public AttenuatedLightComponent
	{
	protected:
		PointLight(ObjectGL::UniformSetter& uniformSetter, const LightType type) noexcept;
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		PointLight(ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual ~PointLight() = default;
	};
}