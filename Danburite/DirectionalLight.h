#pragma once

#include "FullscreenDrawer.h"
#include "OrthoLight.h"
#include "LightBaseComponent.h"
#include "SetupTransaction.h"

namespace Danburite
{
	class DirectionalLight : public OrthoLight, public LightBaseComponent
	{
	private:
		FullscreenDrawer &__fullscreenDrawer = FullscreenDrawer::getInstance();
		SetupTransaction __setupTransaction;

	protected:
		virtual void _onDeploy(DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept override;
		virtual void _onVolumeDrawcall() noexcept override;

	public:
		DirectionalLight(const GLuint index);

		virtual ~DirectionalLight() = default;
	};
}