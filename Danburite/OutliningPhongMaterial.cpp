#include "OutliningPhongMaterial.h"
#include "ProgramFactory.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OutliningPhongMaterial::OutliningPhongMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::OUTLINING_PHONG, vertexType),
		_phongProgram(ProgramFactory::getInstance().getProgram(ProgramType::PHONG)),
		_outlineProgram(ProgramFactory::getInstance().getProgram(ProgramType::OUTLINE))
	{
		useLighting(true);
	}

	void OutliningPhongMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		PhongMaterialComponent::_onDeploy(uniformSetter);
		OutliningMaterialComponent::_onDeploy(uniformSetter);

		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::ALWAYS, 1);
		GLFunctionWrapper::setStencilOperation(
			StencilOperationType::KEEP, StencilOperationType::KEEP, StencilOperationType::REPLACE);

		_phongProgram.bind();
		vertexArray.draw(numInstances);

		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::NOTEQUAL, 1);
		GLFunctionWrapper::setStencilOperation(
			StencilOperationType::KEEP, StencilOperationType::KEEP, StencilOperationType::KEEP);

		_outlineProgram.bind();
		vertexArray.draw(numInstances);

		GLFunctionWrapper::setStencilFunction(DepthStencilFunctionType::ALWAYS, 1);
	}
}