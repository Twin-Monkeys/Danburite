#include "OrthoLight.h"

using namespace ObjectGL;

namespace Danburite
{
	OrthoLight::OrthoLight(UniformSetter &uniformSetter, const LightType type) :
		Light(uniformSetter, type)
	{}
}