#include "MonoColorMaterial.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::MONO_COLOR, vertexFlag),
		_monoColorProgram(ProgramFactory::getInstance().getProgram(ProgramType::MONO_COLOR))
	{
		enableLighting(false);
	}

	void MonoColorMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_monoColorProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void MonoColorMaterial::_onRawDrawcall(
		UniformSetter& materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.setUniformVec4(ShaderIdentifier::Name::Material::DIFFUSE_COLOR, __color);
		vertexArray.draw(numInstances);
	}
}