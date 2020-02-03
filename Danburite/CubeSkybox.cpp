#include "CubeSkybox.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	CubeSkybox::CubeSkybox() noexcept :
		Skybox({ ProgramType::SKYBOX })
	{}

	void CubeSkybox::_onDeploy(SkyboxUniformSetter &target) noexcept
	{
		CubeSkyboxComponent::_onDeploy(target);
	}

	void CubeSkybox::_onDraw(SkyboxUniformSetter &target) noexcept
	{
		target.getProgram(ProgramType::SKYBOX).bind();

		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LEQUAL);
		GLFunctionWrapper::setCulledFace(FrameBufferPositionType::FRONT);
		_drawBoxVA();
		GLFunctionWrapper::setCulledFace(FrameBufferPositionType::BACK);
		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LESS);
	}
}