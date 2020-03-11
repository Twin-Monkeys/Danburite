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
		PointLight(
			const LightType type,
			ObjectGL::UniformSetter &lightParamSetter,
			ObjectGL::UniformSetter &cameraParamSetter) noexcept;

		virtual void _onDeploy(LightUniformSetter &lightParamSetter) noexcept override;

	public:
		PointLight(ObjectGL::UniformSetter &lightParamSetter, ObjectGL::UniformSetter &cameraParamSetter) noexcept;

		virtual ~PointLight() = default;
	};
}