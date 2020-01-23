#pragma once

#include <unordered_map>
#include <unordered_set>
#include "ProgramType.h"
#include "Program.h"

namespace Danburite
{
	class SkyboxUniformSetter
	{
	private:
		std::unordered_map<ProgramType, ObjectGL::Program *> __programMap;

	public:
		SkyboxUniformSetter(const std::unordered_set<ProgramType> &programTypes) noexcept;
		ObjectGL::Program &getProgram(const ProgramType programType) const noexcept;

		virtual ~SkyboxUniformSetter() = default;
	};
}