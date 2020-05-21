#include "AnimationNode.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void AnimationNode::__updateTransform() noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(__timestamp);

		__nodeTransform.setPosition(position);
		__nodeTransform.setRotation(rotation);
		__nodeTransform.setScale(scale);
	}

	AnimationNode &AnimationNode::updateMatrix() noexcept
	{
		__updateTransform();
		__nodeTransform.updateMatrix();

		return *this;
	}
}