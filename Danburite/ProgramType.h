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
		GEOMETRY_DEMO,
		EXPLODING_PHONG,

		// Skybox
		SKYBOX,

		// Post processing programs
		POST_PROCESS_FORWARD,
		POST_PROCESS_NEGATIVE,
		POST_PROCESS_GRAYSCALE,
		POST_PROCESS_CONVOLUTIONAL,
		POST_PROCESS_MSAA
	};
}