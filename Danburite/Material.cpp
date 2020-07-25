#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Material::Material(const MaterialType materialType, const VertexAttributeFlag vertexFlag) noexcept :
		__MATERIAL_TYPE(materialType), __VERTEX_FLAG(vertexFlag),
		__materialSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL))
	{}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::TYPE, GLuint(__MATERIAL_TYPE));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::VERTEX_FLAG, GLuint(__VERTEX_FLAG));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::OPTION_FLAG, GLuint(__optionFlag));

		_onRender(__materialSetter, vertexArray, numInstances);
	}

	void Material::rawDrawcall(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::TYPE, GLuint(__MATERIAL_TYPE));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::VERTEX_FLAG, GLuint(__VERTEX_FLAG));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::OPTION_FLAG, GLuint(__optionFlag));

		_onRawDrawcall(__materialSetter, vertexArray, numInstances);
	}

	void Material::setGamma(const float gamma)
	{
		UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL).
			setUniformFloat(ShaderIdentifier::Name::Material::GAMMA, gamma);
	}
}