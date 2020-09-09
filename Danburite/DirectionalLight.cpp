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

	void DirectionalLight::_onDeploy(LightUniformInterface &lightUI) noexcept
	{
		_deployBaseComponent(getIndex(), lightUI);
		_deployDirection(lightUI);
	}

	void DirectionalLight::_onVolumeDrawcall() noexcept
	{
		__setupTransaction();
		__fullscreenDrawer.draw();
	}
}
