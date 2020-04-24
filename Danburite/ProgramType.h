#pragma once

namespace Danburite
{
	enum class ProgramType
	{
		// Normal programs
		MONO_COLOR,
		PHONG,
		SILHOUETTE,
		OUTLINE,
		REFLECTION,
		REFLECTION_PHONG,
		REFRACTION,

		// Skybox
		SKYBOX,

		// Post processing programs
		POST_PROCESS_FORWARD,
		POST_PROCESS_NEGATIVE,
		POST_PROCESS_GRAYSCALE,
		POST_PROCESS_CONVOLUTIONAL,
		POST_PROCESS_MSAA,
		POST_PROCESS_GAMMA_CORRECTION,
		POST_PROCESS_HDR,

		// Depth baking
		DEPTH_BAKING_2D,
		DEPTH_BAKING_CUBEMAP
	};

	constexpr ProgramType operator+(const ProgramType lhs, const int rhs) noexcept
	{
		return ProgramType(int(lhs) + rhs);
	}

	constexpr ProgramType operator++(ProgramType &type, int) noexcept
	{
		const ProgramType retVal = type;
		type = (type + 1);

		return retVal;
	}
}