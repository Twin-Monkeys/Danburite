#include "AnimatableTransform.h"
#include "Constant.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void AnimatableTransform::updateMatrix(const float deltaTime) noexcept
	{
		if (__animEnabled)
			__animation.adjustTimestamp(deltaTime).updateState();

		__animatedTransformComponent.position =
			(__animation.getCurrentState().position + getPosition());

		__animatedTransformComponent.scale =
			(__animation.getCurrentState().scale * getScale());

		__animatedTransformComponent.rotation =
			(__animation.getCurrentState().rotation * getRotation());

		Transform::updateMatrix(deltaTime);
	}
}