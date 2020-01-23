#pragma once

#include "MaterialUniformDeployable.h"
#include "Constant.h"

namespace Danburite
{
	class SilhouetteMaterialComponent : virtual public MaterialUniformDeployable
	{
	private:
		float __zNear = Constant::Camera::Z_NEAR;
		float __zFar = Constant::Camera::Z_FAR;

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;

	public:
		void setNearFar(const float zNear, const float zFar) noexcept;

		virtual ~SilhouetteMaterialComponent() = default;
	};
}