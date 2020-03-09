#pragma once

#include "UniformDeployable.h"
#include "TextureCubemap.h"
#include "UniformSetter.h"
#include <memory>

namespace Danburite
{
	class CubeSkyboxComponent : public ObjectGL::UniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pAlbedoTex;

	protected:
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) const noexcept override;

	public:
		void setAlbedoTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;

		virtual ~CubeSkyboxComponent() = default;
	};
}