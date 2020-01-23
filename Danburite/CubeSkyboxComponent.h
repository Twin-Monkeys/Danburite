#pragma once

#include "SkyboxUniformDeployable.h"
#include "TextureCubemap.h"

namespace Danburite
{
	class CubeSkyboxComponent : virtual public SkyboxUniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pAlbedoTex;

	protected:
		virtual void _onDeploy(SkyboxUniformSetter &target) noexcept override;

	public:
		void setAlbedoTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
	};
}