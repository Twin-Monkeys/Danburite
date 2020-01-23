 #pragma once

#include <glm/glm.hpp>
#include "LightUniformDeployable.h"

namespace Danburite
{
	class LightBaseComponent abstract : virtual public LightUniformDeployable
	{
	private:
		glm::vec3 __albedo = { 1.f, 1.f, 1.f };
		float __ambientStrength = .3f;
		float __diffuseStrength = .8f;
		float __specularStrength = .6f;

	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		const glm::vec3 &getAlbedo() const noexcept;
		void setAlbedo(const glm::vec3 &albedo) noexcept;
		void setAlbedo(const float r, const float g, const float b) noexcept;

		float getAmbientStrength() const noexcept;
		void setAmbientStrength(const float strength) noexcept;

		float getDiffuseStrength() const noexcept;
		void setDiffuseStrength(const float strength) noexcept;

		float getSpecularStrength() const noexcept;
		void setSpecularStrength(const float strength) noexcept;

		virtual ~LightBaseComponent() = default;
	};
}