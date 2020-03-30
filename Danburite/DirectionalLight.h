#pragma once

#include "OrthoCameraLight.h"
#include "LightBaseComponent.h"

namespace Danburite
{
	class DirectionalLight : public OrthoCameraLight, public LightBaseComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &lightParamSetter) noexcept override;

	public:
		DirectionalLight();

		virtual ~DirectionalLight() = default;
	};
}