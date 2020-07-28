#include "CubeSkybox.h"
#include "GLFunctionWrapper.h"
#include "ProgramFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	CubeSkybox::CubeSkybox() noexcept :
		__skyboxProgram(ProgramFactory::getInstance().getProgram(ProgramType::SKYBOX))
	{}

	void CubeSkybox::_onDraw(UniformBuffer &skyBoxSetter, VertexArray &cubeVA) noexcept
	{
		_deployCubeCkyboxComponent(skyBoxSetter);

		__skyboxProgram.bind();

		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LEQUAL);
		GLFunctionWrapper::setCulledFace(FacetType::FRONT);
		cubeVA.draw();
		GLFunctionWrapper::setCulledFace(FacetType::BACK);
		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LESS);
	}
}