#pragma once

#include <glm/glm.hpp>
#include "UniformSetter.h"

namespace Danburite
{
	class MonoColorMaterialComponent
	{
	private:
		glm::vec4 __color { 1.f, 1.f, 1.f, 1.f };

	protected:
		void _deployMonoColorComponent(ObjectGL::UniformSetter &materialSetter) const noexcept;

	public:
		constexpr void setColor(const glm::vec4 &color) noexcept;

		virtual ~MonoColorMaterialComponent() = default;
	};

	constexpr void MonoColorMaterialComponent::setColor(const glm::vec4 &color) noexcept
	{
		__color = color;
	}
}