#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include "UniformSetter.h"

namespace Danburite
{
	class OutliningMaterialComponent
	{
	private:
		glm::vec4 __outlineColor { .1f, .2f, .9f, 1.f };
		GLfloat __outlineThicknessRatio = 1.05f;

	protected:
		void _deployOutliningComponent(ObjectGL::UniformSetter &materialSetter) const noexcept;

	public:
		constexpr void setOutlineColor(const glm::vec4 &color) noexcept;
		constexpr void setOutlineThicknessRatio(const GLfloat thicknessRatio) noexcept;

		virtual ~OutliningMaterialComponent() = default;
	};

	constexpr void OutliningMaterialComponent::setOutlineColor(const glm::vec4 &color) noexcept
	{
		__outlineColor = color;
	}

	constexpr void OutliningMaterialComponent::setOutlineThicknessRatio(const GLfloat thicknessRatio) noexcept
	{
		__outlineThicknessRatio = thicknessRatio;
	}
}