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
		__uniformSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL))
	{}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__uniformSetter.setUniformUint(ShaderIdentifier::Name::Material::TYPE, GLenum(__MATERIAL_TYPE));
		__uniformSetter.setUniformUint(ShaderIdentifier::Name::Material::VERTEX_FLAG, GLenum(__VERTEX_TYPE));
		__uniformSetter.setUniformUint(ShaderIdentifier::Name::Material::OPTION_FLAG, GLenum(__optionFlag));
		__uniformSetter.setUniformFloat(ShaderIdentifier::Name::Material::GAMMA, __gamma);

		_onRender(__uniformSetter, vertexArray, numInstances);
	}
}