#include "PhongMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PhongMaterial::PhongMaterial(
		const MaterialType materialType,
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		Material(materialType, vertexType, uniformSetter),
		_phongProgram(ProgramFactory::getInstance().getProgram(ProgramType::PHONG))
	{
		useLighting(true);
	}

	PhongMaterial::PhongMaterial(
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		PhongMaterial(MaterialType::PHONG, vertexType, uniformSetter)
	{}

	void PhongMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_phongProgram.bind();
		vertexArray.draw(numInstances);
	}
}