#pragma once

#include "Constant.h"
#include "UniformSetter.h"

namespace Danburite
{
	class SilhouetteMaterialComponent
	{
	private:
		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;

	protected:
		void _deploySilhouetteComponent(ObjectGL::UniformSetter &materialSetter) const noexcept;

	public:
		constexpr void setNearFar(const float zNear, const float zFar) noexcept;

		virtual ~SilhouetteMaterialComponent() = default;
	};

	constexpr void SilhouetteMaterialComponent::setNearFar(const float zNear, const float zFar) noexcept
	{
		__zNear = zNear;
		__zFar = zFar;
	}
}