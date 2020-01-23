#include "OutliningPhongMaterial.h"
#include "ShaderIdentifier.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OutliningPhongMaterial::OutliningPhongMaterial(const VertexAttributeType vertexType) noexcept :
		PhongMaterial({ ProgramType::OUTLINE, ProgramType::PHONG }, MaterialType::OUTLINING_PHONG, vertexType)
	{
		useLighting(true);
	}

	void OutliningPhongMaterial::_onDeploy(MaterialUniformSetter &materialUniformSetter) noexcept
	{
		PhongMaterial::_onDeploy(materialUniformSetter);
		OutliningMaterialComponent::_onDeploy(materialUniformSetter);
	}

	void OutliningPhongMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::ALWAYS, 1);
		GLFunctionWrapper::setStencilOperation(
			StencilOperationType::KEEP, StencilOperationType::KEEP, StencilOperationType::REPLACE);

		target.getProgram(ProgramType::PHONG).bind();
		vertexArray.draw(numInstances);

		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::NOTEQUAL, 1);
		GLFunctionWrapper::setStencilOperation(
			StencilOperationType::KEEP, StencilOperationType::KEEP, StencilOperationType::KEEP);

		target.getProgram(ProgramType::OUTLINE).bind();
		vertexArray.draw(numInstances);

		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::ALWAYS, 1);
	}
}