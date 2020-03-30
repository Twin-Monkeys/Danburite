#include "RefractionMaterial.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RefractionMaterial::RefractionMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::REFRACTION, vertexType),
		_refractionProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFRACTION))
	{}

	void RefractionMaterial::_onRender(UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_refractionProgram.bind();
		vertexArray.draw(numInstances);
	}
}