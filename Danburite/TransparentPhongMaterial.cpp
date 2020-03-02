#include "TransparentPhongMaterial.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	TransparentPhongMaterial::TransparentPhongMaterial(
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		PhongMaterial(MaterialType::TRANSPARENT_PHONG, vertexType, uniformSetter)
	{}

	void TransparentPhongMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		GLFunctionWrapper::setOption(GLOptionType::BLEND, true);
		GLFunctionWrapper::setBlendingFunction(
			BlendingFunctionType::SRC_ALPHA, BlendingFunctionType::ONE_MINUS_SRC_ALPHA);

		GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, false);
		GLFunctionWrapper::setDepthMask(false);

		_phongProgram.bind();
		vertexArray.draw(numInstances);

		GLFunctionWrapper::setDepthMask(true);
		GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);
		GLFunctionWrapper::setOption(GLOptionType::BLEND, false);
	}
}