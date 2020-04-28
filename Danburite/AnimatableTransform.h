#pragma once

#include <map>
#include "Transform.h"

namespace Danburite
{
	class AnimatableTransform
	{
	private:
		Transform __animationTransform;
		Transform __modelTransform;
	};
}
