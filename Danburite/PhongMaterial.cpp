#include "PhongMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PhongMaterial::PhongMaterial(const MaterialType materialType, const VertexAttributeType vertexType) noexcept :
		Material(materialType, vertexType),
		_phongProgram(ProgramFactory::getInstance().getProgram(ProgramType::PHONG))
	{
		useLighting(true);
	}

	PhongMaterial::PhongMaterial(const VertexAttributeType vertexType) noexcept :
		PhongMaterial(MaterialType::PHONG, vertexType)
	{}

	void PhongMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_phongProgram.bind();
		vertexArray.draw(numInstances);
	}
}