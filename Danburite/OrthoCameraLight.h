#pragma once

#include "TransformableCameraLight.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class OrthoCameraLight abstract : public TransformableCameraLight
	{
	private:
		OrthoCamera __camera;

	protected:
		virtual TransformableCamera &_getCamera() noexcept override;
		virtual const TransformableCamera &_getCamera() const noexcept override;

	public:
		OrthoCameraLight(
			const LightType type,
			ObjectGL::UniformSetter &lightParamSetter,
			ObjectGL::UniformSetter &cameraParamSetter);
	};
}