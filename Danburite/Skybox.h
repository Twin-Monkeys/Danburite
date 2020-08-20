#pragma once

#include "VertexArray.h"
#include "UniformBuffer.h"
#include "TextureCubemap.h"
#include "VertexArrayFactory.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "SetupTransaction.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class Skybox
	{
	private:
		bool __enabled = false;

		ObjectGL::UniformBuffer &__skyboxSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::SKYBOX);

		ObjectGL::Program &__skyboxProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::SKYBOX);

		std::shared_ptr<ObjectGL::VertexArray> __pCubeVA =
			VertexArrayFactory::createCube(VertexAttributeFlag::POS);

		std::shared_ptr<ObjectGL::TextureCubemap> __pAlbedoTex;
		float __luminance = 1.f;

		SetupTransaction __setupTransaction;

	public:
		Skybox();

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		void setAlbedoTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
		void setLuminance(const float luminance) noexcept;

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
