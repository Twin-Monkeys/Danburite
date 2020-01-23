#pragma once

#include "MaterialUniformDeployable.h"

namespace Danburite
{
	class MonoColorMaterialComponent : virtual public MaterialUniformDeployable
	{
	private:
		glm::vec4 __color { 1.f, 1.f, 1.f, 1.f };

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;

	public:
		void setColor(const glm::vec4 &color) noexcept;

		virtual ~MonoColorMaterialComponent() = default;
	};
}