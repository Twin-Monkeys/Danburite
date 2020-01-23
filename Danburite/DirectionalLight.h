#pragma once

#include "Light.h"
#include "LightBaseComponent.h"
#include "DirectionalLightComponent.h"

namespace Danburite
{
	class DirectionalLight :
		public Light, public LightBaseComponent, public DirectionalLightComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		DirectionalLight(ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual ~DirectionalLight() = default;
	};
}