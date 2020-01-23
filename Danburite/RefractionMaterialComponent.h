#pragma once

#include "MaterialUniformDeployable.h"
#include "TextureCubemap.h"
#include "Texture2D.h"

namespace Danburite
{
	class RefractionMaterialComponent : virtual public MaterialUniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;

	public:
		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		virtual ~RefractionMaterialComponent() = default;
	};
}
