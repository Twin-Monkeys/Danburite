#include "PerspectiveCameraLight.h"

using namespace ObjectGL;

namespace Danburite
{
	PerspectiveCameraLight::PerspectiveCameraLight(const LightType type) :
		TransformableCameraLight(type)
	{}

	TransformableCamera &PerspectiveCameraLight::_getCamera() noexcept
	{
		return __camera;
	}

	const TransformableCamera &PerspectiveCameraLight::_getCamera() const noexcept
	{
		return __camera;
	}
}