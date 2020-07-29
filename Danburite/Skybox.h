#pragma once

#include "VertexArray.h"
#include "UniformBuffer.h"
#include "TextureCubemap.h"

namespace Danburite
{
	class Skybox
	{
	private:
		ObjectGL::UniformBuffer &__skyboxSetter;
		ObjectGL::Program &__skyboxProgram;

		std::shared_ptr<ObjectGL::TextureCubemap> __pAlbedoTex;
		std::shared_ptr<ObjectGL::VertexArray> __pCubeVA;

		bool __enabled = false;

	public:
		Skybox();

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		void setAlbedoTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;

		void draw() noexcept;

		virtual ~Skybox() = default;
	};

	constexpr bool Skybox::isEnabled() const noexcept
	{
		return __enabled;
	}

	constexpr void Skybox::setEnabled(const bool enabled) noexcept
	{
		__enabled = enabled;
	}
}
