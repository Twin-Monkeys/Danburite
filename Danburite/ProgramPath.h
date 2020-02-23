#pragma once

#include <string>
#include "ProgramType.h"
#include "ProgramPathType.h"

namespace Danburite
{
	class ProgramPath abstract
	{
	public:
		static const std::string &getPath(const ProgramPathType pathType, const ProgramType programType) noexcept;
	};
}
