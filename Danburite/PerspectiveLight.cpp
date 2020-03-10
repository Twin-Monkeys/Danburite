#include "PerspectiveLight.h"

using namespace ObjectGL;

namespace Danburite
{
	PerspectiveLight::PerspectiveLight(UniformSetter &uniformSetter, const LightType type) :
		Light(uniformSetter, type)
	{}
}