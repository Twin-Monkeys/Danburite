#include "TransparentPhongMaterial.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	TransparentPhongMaterial::TransparentPhongMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		PhongMaterial(MaterialType::TRANSPARENT_PHONG, vertexFlag)
	{}

	void TransparentPhongMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		GLFunctionWrapper::setOption(GLOptionType::BLEND, true);
		GLFunctionWrapper::setBlendingFunction(
			BlendingFunctionType::SRC_ALPHA, BlendingFunctionType::ONE_MINUS_SRC_ALPHA);

		GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, false);
		GLFunctionWrapper::setDepthMask(false);

		PhongMaterial::_onRender(materialSetter, vertexArray, numInstances);

		GLFunctionWrapper::setDepthMask(true);
		GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);
		GLFunctionWrapper::setOption(GLOptionType::BLEND, false);
	}
}