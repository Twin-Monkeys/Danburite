#pragma once

#include "TransformableCameraLight.h"
#include "PerspectiveCamera.h"

namespace Danburite
{
	class PerspectiveCameraLight abstract : public TransformableCameraLight
	{
	private:
		PerspectiveCamera __camera;

	protected:
		virtual TransformableCamera &_getCamera() noexcept override;
		virtual const TransformableCamera &_getCamera() const noexcept override;

	public:
		PerspectiveCameraLight(
			const LightType type,
			ObjectGL::UniformSetter& lightParamSetter,
			ObjectGL::UniformSetter& cameraParamSetter);
	};
}