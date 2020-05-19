#pragma once

#include <glm/glm.hpp>
#include "Quaternion.h"

namespace Danburite
{
	class Lerp abstract final
	{
	public:
		template <typename T>
		static T interpolate(const T &lhs, const T &rhs, const float weight) noexcept;

		template <>
		static Quaternion interpolate(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept;

		template <typename T>
		static T extrapolate(const T &lhs, const T &rhs, const float weight) noexcept;

		template <>
		static Quaternion extrapolate(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept;
	};

	template <typename T>
	T Lerp::interpolate(const T &lhs, const T &rhs, const float weight) noexcept
	{
		return glm::mix(lhs, rhs, weight);
	}

	template <>
	Quaternion Lerp::interpolate(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept
	{
		return Quaternion::slerp(lhs, rhs, weight);
	}

	template <typename T>
	T Lerp::extrapolate(const T &lhs, const T &rhs, const float weight) noexcept
	{
		return (lhs + ((lhs - rhs) * weight));
	}

	template <>
	Quaternion Lerp::extrapolate(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept
	{
		const auto &[angle, axis] = (rhs * lhs.inverse()).getAngleAxis();
		return { -(angle * weight), axis };
	}
}
