#pragma once

#include "OrthoLight.h"
#include "LightBaseComponent.h"

namespace Danburite
{
	class DirectionalLight : public OrthoLight, public LightBaseComponent
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		DirectionalLight(ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual void bakeDepthMap() noexcept override;

		virtual ~DirectionalLight() = default;
	};
}