#pragma once

#include <glm/glm.hpp>
#include "Quaternion.h"

namespace Danburite
{
	class TransformComponent
	{
	public:
		glm::vec3	position	{ 0.f, 0.f, 0.f };
		glm::vec3	scale		{ 1.f, 1.f, 1.f };
		Quaternion	rotation;

		static TransformComponent mix(
			const TransformComponent &lhs, const TransformComponent &rhs, const float weight) noexcept;
	};
}
