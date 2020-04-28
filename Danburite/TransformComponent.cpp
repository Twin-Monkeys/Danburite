#include "TransformComponent.h"

namespace Danburite
{
	TransformComponent TransformComponent::mix(
		const TransformComponent &lhs, const TransformComponent &rhs, const float weight) noexcept
	{
		return
		{
			glm::mix(lhs.position, rhs.position, weight),
			glm::mix(lhs.scale, rhs.scale, weight),
			Quaternion::slerp(lhs.rotation, rhs.rotation, weight)
		};
	}
}