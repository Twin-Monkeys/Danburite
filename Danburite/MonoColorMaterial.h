#pragma once

#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class MonoColorMaterial : public Material
	{
	private:
		ObjectGL::Program &__monoColorProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::MONO_COLOR);

		glm::vec4 __color { 1.f, 1.f, 1.f, 1.f };

	protected:
		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		MonoColorMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		constexpr void setColor(const glm::vec4 &color) noexcept;

		virtual ~MonoColorMaterial() = default;
	};

	constexpr void MonoColorMaterial::setColor(const glm::vec4 &color) noexcept
	{
		__color = color;
	}
}