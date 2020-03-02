#pragma once

#include "UniformDeployable.h"

namespace Danburite
{
	class OutliningMaterialComponent : public ObjectGL::UniformDeployable
	{
	private:
		glm::vec4 __outlineColor { .1f, .2f, .9f, 1.f };
		GLfloat __outlineThicknessRatio = 1.05f;

	protected:
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

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