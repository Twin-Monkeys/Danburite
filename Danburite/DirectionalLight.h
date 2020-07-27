#pragma once

#include "FullscreenDrawer.h"
#include "OrthoLight.h"
#include "LightBaseComponent.h"

namespace Danburite
{
	class DirectionalLight : public OrthoLight, public LightBaseComponent
	{
	private:
		FullscreenDrawer __fullscreenDrawer;

	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		DirectionalLight();
		virtual void volumeDrawcall() noexcept override;

		virtual ~DirectionalLight() = default;
	};
}