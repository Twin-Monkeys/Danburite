#pragma once

#include <map>
#include "Transform.h"

namespace Danburite
{
	class AnimatableTransform
	{
	private:
		std::map<float, TransformComponent> __keyframes;

	public:
		Transform __animationTransform;
		Transform __modelTransform;
	};
}
