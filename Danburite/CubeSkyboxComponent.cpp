#include "CubeSkyboxComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void CubeSkyboxComponent::_onDeploy(SkyboxUniformSetter &target) noexcept
	{
		TextureUtil::bindIfExist(__pAlbedoTex, ShaderIdentifier::Value::Cubemap::ALBEDO_TEX_LOCATION);
	}

	void CubeSkyboxComponent::setAlbedoTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pAlbedoTex = pTexture;
	}
}