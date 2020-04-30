#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Material::Material(const MaterialType materialType, const VertexAttributeType vertexType) noexcept :
		__MATERIAL_TYPE(materialType), __VERTEX_TYPE(vertexType),
		__materialSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL))
	{}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::TYPE, GLenum(__MATERIAL_TYPE));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::VERTEX_FLAG, GLenum(__VERTEX_TYPE));
		__materialSetter.setUniformUint(ShaderIdentifier::Name::Material::OPTION_FLAG, GLenum(__optionFlag));

		_onRender(__materialSetter, vertexArray, numInstances);
	}
}