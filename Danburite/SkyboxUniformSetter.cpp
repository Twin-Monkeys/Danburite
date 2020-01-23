#include "SkyboxUniformSetter.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	SkyboxUniformSetter::SkyboxUniformSetter(const unordered_set<ProgramType> &programTypes) noexcept
	{
		ProgramFactory &programFactory = ProgramFactory::getInstance();

		for (const ProgramType programType : programTypes)
			__programMap.emplace(programType, &(programFactory.getProgram(programType)));
	}

	Program &SkyboxUniformSetter::getProgram(const ProgramType programType) const noexcept
	{
		return *__programMap.at(programType);
	}
}