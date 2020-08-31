#include "DirectionalLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(const GLuint index) :
		OrthoLight(LightType::DIRECTIONAL, index)
	{
		__setupTransaction.setup([this](ContextStateManager &stateMgr)
		{
			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);
			stateMgr.setCulledFace(FacetType::BACK);
		});
	}

	void DirectionalLight::_onDeploy(DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept
	{
		_deployBaseComponent(getIndex(), lightUB);
		_deployDirection(lightUB);
	}

	void DirectionalLight::_onVolumeDrawcall() noexcept
	{
		__setupTransaction();
		__fullscreenDrawer.draw();
	}
}
