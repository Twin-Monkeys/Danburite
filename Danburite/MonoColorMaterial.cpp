#include "MonoColorMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::MONO_COLOR, vertexFlag)
	{
		enableLighting(false);
	}

	void MonoColorMaterial::_onRender(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__monoColorProgram.bind();
		_onRawDrawcall(materialUB, vertexArray, numInstances);
	}

	void MonoColorMaterial::_onRawDrawcall(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		MaterialUniformInterface &materialUniformInterface = materialUB.getInterface();
		materialUniformInterface.diffuseColor = __color;

		materialUB.selfDeploy();
		vertexArray.draw(numInstances);
	}
}