#pragma once

#include "Skybox.h"
#include "CubeSkyboxComponent.h"

namespace Danburite
{
	class CubeSkybox : public Skybox, public CubeSkyboxComponent
	{
	protected:
		virtual void _onDeploy(SkyboxUniformSetter &target) noexcept override;
		virtual void _onDraw(SkyboxUniformSetter &target) noexcept override;

	public:
		CubeSkybox() noexcept;

		virtual ~CubeSkybox() = default;
	};
}