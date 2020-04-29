#include "AnimatableTransform.h"
#include "Constant.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void AnimatableTransform::updateMatrix(const float deltaTime) noexcept
	{
		__animation.update(deltaTime);

		__animatedTransformComponent.position =
			(getPosition() + __animation.getCurrentState().position);

		__animatedTransformComponent.scale =
			(getScale() * __animation.getCurrentState().scale);

		__animatedTransformComponent.rotation =
			(getRotation() * __animation.getCurrentState().rotation);

		Transform::updateMatrix(deltaTime);
	}
}