#include "CubeSkybox.h"
#include "GLFunctionWrapper.h"
#include "ProgramFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	CubeSkybox::CubeSkybox(UniformSetter &uniformSetter) noexcept :
		Skybox(uniformSetter),
		__skyboxProgram(ProgramFactory::getInstance().getProgram(ProgramType::SKYBOX))
	{}

	void CubeSkybox::_onDraw(UniformSetter &uniformSetter) noexcept
	{
		uniformSetter.directDeploy(*this);

		__skyboxProgram.bind();

		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LEQUAL);
		GLFunctionWrapper::setCulledFace(FrameBufferPositionType::FRONT);
		_drawBoxVA();
		GLFunctionWrapper::setCulledFace(FrameBufferPositionType::BACK);
		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LESS);
	}
}