#pragma once

#include <tuple>

namespace Danburite
{
	enum class EulerAngleOrder : unsigned
	{
		PITCH_YAW_ROLL = 0U,
		PITCH_ROLL_YAW,
		YAW_PITCH_ROLL,
		YAW_ROLL_PITCH,
		ROLL_PITCH_YAW,
		ROLL_YAW_PITCH
	};

	constexpr unsigned EulerAngleOrder_enumToArr[][3] =
	{
		{ 0U, 1U, 2U },
		{ 0U, 2U, 1U },
		{ 1U, 0U, 2U },
		{ 1U, 2U, 0U },
		{ 2U, 0U, 1U },
		{ 2U, 1U, 0U }
	};

	constexpr const unsigned(&enumToArr(const EulerAngleOrder order))[3]
	{
		return EulerAngleOrder_enumToArr[unsigned(order)];
	}
}