#pragma once

#include <unordered_map>
#include "ProgramType.h"
#include <string>
#include "ProgramPathType.h"
#include "AssertException.h"
#include <array>

namespace Danburite
{
	class ProgramPath abstract
	{
	public:
		static const std::string &getPath(const ProgramPathType pathType, const ProgramType programType) noexcept;
	};
}
