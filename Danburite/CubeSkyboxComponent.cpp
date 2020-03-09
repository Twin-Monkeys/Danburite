#include "CubeSkyboxComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void CubeSkyboxComponent::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		uniformSetter.setUniformUvec2(
			ShaderIdentifier::Name::Cubemap::ALBEDO_TEX, TextureUtil::getHandleIfExist(__pAlbedoTex));
	}

	void CubeSkyboxComponent::setAlbedoTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pAlbedoTex = pTexture;
	}
}