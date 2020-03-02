#pragma once

#include "UniformDeployable.h"
#include "Constant.h"

namespace Danburite
{
	class SilhouetteMaterialComponent : public ObjectGL::UniformDeployable
	{
	private:
		float __zNear = Constant::Camera::Z_NEAR;
		float __zFar = Constant::Camera::Z_FAR;

	protected:
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

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