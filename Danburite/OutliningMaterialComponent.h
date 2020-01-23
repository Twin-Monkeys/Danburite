#pragma once

#include "MaterialUniformDeployable.h"

namespace Danburite
{
	class OutliningMaterialComponent : virtual public MaterialUniformDeployable
	{
	private:
		glm::vec4 __outlineColor { .1f, .2f, .9f, 1.f };
		GLfloat __outlineThicknessRatio = 1.05f;

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;

	public:
		void setOutlineColor(const glm::vec4 &color) noexcept;
		void setOutlineThicknessRatio(const GLfloat thicknessRatio) noexcept;

		virtual ~OutliningMaterialComponent() = default;
	};
}