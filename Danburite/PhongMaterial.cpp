#include "PhongMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PhongMaterial::PhongMaterial(const MaterialType materialType, const VertexAttributeFlag vertexFlag) noexcept :
		Material(materialType, vertexFlag),
		_phongProgram(ProgramFactory::getInstance().getProgram(ProgramType::PHONG))
	{
		useLighting(true);
	}

	PhongMaterial::PhongMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		PhongMaterial(MaterialType::PHONG, vertexFlag)
	{}

	void PhongMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_phongProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void PhongMaterial::_onRawDrawcall(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_deployPhongComponent(materialSetter);
		vertexArray.draw(numInstances);
	}
}