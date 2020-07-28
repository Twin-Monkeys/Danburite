#pragma once

#include "TextureCubemap.h"
#include "UniformBuffer.h"
#include <memory>

namespace Danburite
{
	class CubeSkyboxComponent
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pAlbedoTex;

	protected:
		void _deployCubeCkyboxComponent(ObjectGL::UniformBuffer &skyboxSetter) const noexcept;

	public:
		void setAlbedoTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;

		virtual ~CubeSkyboxComponent() = default;
	};
}