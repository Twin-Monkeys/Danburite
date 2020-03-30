#include "OrthoCameraLight.h"

using namespace ObjectGL;

namespace Danburite
{
	OrthoCameraLight::OrthoCameraLight(const LightType type) :
		TransformableCameraLight(type)
	{}

	TransformableCamera &OrthoCameraLight::_getCamera() noexcept
	{
		return __camera;
	}

	const TransformableCamera &OrthoCameraLight::_getCamera() const noexcept
	{
		return __camera;
	}
}