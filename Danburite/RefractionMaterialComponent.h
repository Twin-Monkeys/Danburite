#pragma once

#include "UniformDeployable.h"
#include "TextureCubemap.h"
#include "Texture2D.h"
#include <memory>

namespace Danburite
{
	class RefractionMaterialComponent : public ObjectGL::UniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

	protected:
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

	public:
		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		virtual ~RefractionMaterialComponent() = default;
	};
}
