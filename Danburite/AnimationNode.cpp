#include "AnimationNode.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void AnimationNode::__updateTransform(const float timestamp) noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(timestamp);

		__currentTransform.setPosition(position);
		__currentTransform.setRotation(rotation);
		__currentTransform.setScale(scale);
	}

	void AnimationNode::updateMatrix() noexcept
	{
		__updateTransform(__timestamp);
		__currentTransform.updateMatrix();

		__nodeMat = __currentTransform.getModelMatrix();
	}

	void AnimationNode::updateMatrix(const mat4 &parentMatrix) noexcept
	{
		__updateTransform(__timestamp);
		__currentTransform.updateMatrix();

		__nodeMat = (parentMatrix * __currentTransform.getModelMatrix());
	}
}