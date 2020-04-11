#pragma once

#include "OrthoLight.h"
#include "LightBaseComponent.h"

namespace Danburite
{
	class DirectionalLight : public OrthoLight, public LightBaseComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		DirectionalLight();

		virtual ~DirectionalLight() = default;
	};
}