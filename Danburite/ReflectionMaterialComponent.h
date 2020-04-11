#pragma once

#include "TextureCubemap.h"
#include "Texture2D.h"
#include <memory>
#include "UniformSetter.h"

namespace Danburite
{
	class ReflectionMaterialComponent
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

	protected:
		void _deployReflectionComponent(ObjectGL::UniformSetter &materialSetter) const noexcept;

	public:
		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		virtual ~ReflectionMaterialComponent() = default;
	};
}
