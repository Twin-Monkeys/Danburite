#include "MaterialUniformSetter.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MaterialUniformSetter::MaterialUniformSetter(const unordered_set<ProgramType> &programTypes) noexcept
	{
		ProgramFactory &programFactory = ProgramFactory::getInstance();

		for (const ProgramType programType : programTypes)
			__programMap.emplace(programType, &(programFactory.getProgram(programType)));
	}

	Program &MaterialUniformSetter::getProgram(const ProgramType programType) const noexcept
	{
		return *__programMap.at(programType);
	}

	void MaterialUniformSetter::setMaterialType(const MaterialType type) noexcept
	{
		traverseProgram(&Program::setUniformUint, ShaderIdentifier::Name::Material::TYPE, GLenum(type));
	}

	void MaterialUniformSetter::setVertexType(const VertexAttributeType type) noexcept
	{
		traverseProgram(&Program::setUniformUint, ShaderIdentifier::Name::Material::VERTEX_FLAG, GLenum(type));
	}

	void MaterialUniformSetter::setOptionFlag(const MaterialOptionFlag flag) noexcept
	{
		traverseProgram(&Program::setUniformUint, ShaderIdentifier::Name::Material::OPTION_FLAG, GLuint(flag));
	}
}