 #pragma once

#include <glm/glm.hpp>
#include "DeferredUniformBuffer.h"
#include "LightUniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightBaseComponent abstract
	{
	private:
		glm::vec3 __albedo			= Constant::Light::BaseComponent::ALBEDO;
		float __ambientStrength		= Constant::Light::BaseComponent::AMBIENT_STRENGTH;
		float __diffuseStrength		= Constant::Light::BaseComponent::DIFFUSE_STRENGH;
		float __specularStrength	= Constant::Light::BaseComponent::SPECULAR_STRENGH;

	protected:
		void _deployBaseComponent(const size_t lightIndex, DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept;

	public:
		constexpr const glm::vec3 &getAlbedo() const noexcept;
		virtual void setAlbedo(const glm::vec3 &albedo) noexcept;
		void setAlbedo(const float r, const float g, const float b) noexcept;

		constexpr float getAmbientStrength() const noexcept;
		virtual void setAmbientStrength(const float strength) noexcept;

		constexpr float getDiffuseStrength() const noexcept;
		virtual void setDiffuseStrength(const float strength) noexcept;

		constexpr float getSpecularStrength() const noexcept;
		virtual void setSpecularStrength(const float strength) noexcept;

		virtual ~LightBaseComponent() = default;
	};

	constexpr const glm::vec3 &LightBaseComponent::getAlbedo() const noexcept
	{
		return __albedo;
	}

	constexpr float LightBaseComponent::getAmbientStrength() const noexcept
	{
		return __ambientStrength;
	}

	constexpr float LightBaseComponent::getDiffuseStrength() const noexcept
	{
		return __diffuseStrength;
	}

	constexpr float LightBaseComponent::getSpecularStrength() const noexcept
	{
		return __specularStrength;
	}
}