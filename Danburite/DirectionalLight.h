#pragma once

#include "Light.h"
#include "LightBaseComponent.h"
#include "DirectionalLightComponent.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class DirectionalLight :
		public Light, public LightBaseComponent, public DirectionalLightComponent
	{
	private:
		OrthoCamera __depthBakingCamera;

	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		DirectionalLight(ObjectGL::UniformSetter &uniformSetter) noexcept;

		void bakeDepthMap() noexcept override;

		virtual ~DirectionalLight() = default;
	};
}