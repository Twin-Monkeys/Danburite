 #pragma once

#include <glm/glm.hpp>
#include "LightUniformDeployable.h"

namespace Danburite
{
	class LightBaseComponent abstract : virtual public LightUniformDeployable
	{
	private:
		glm::vec3 __albedo = { 1.f, 1.f, 1.f };
		float __ambientStrength = .1f;
		float __diffuseStrength = .8f;
		float __specularStrength = .6f;

	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		constexpr const glm::vec3 &getAlbedo() const noexcept;
		constexpr void setAlbedo(const glm::vec3 &albedo) noexcept;
		constexpr void setAlbedo(const float r, const float g, const float b) noexcept;

		constexpr float getAmbientStrength() const noexcept;
		constexpr void setAmbientStrength(const float strength) noexcept;

		constexpr float getDiffuseStrength() const noexcept;
		constexpr void setDiffuseStrength(const float strength) noexcept;

		constexpr float getSpecularStrength() const noexcept;
		constexpr void setSpecularStrength(const float strength) noexcept;

		virtual ~LightBaseComponent() = default;
	};

	constexpr const glm::vec3 &LightBaseComponent::getAlbedo() const noexcept
	{
		return __albedo;
	}

	constexpr void LightBaseComponent::setAlbedo(const glm::vec3 &albedo) noexcept
	{
		__albedo = albedo;
	}

	constexpr void LightBaseComponent::setAlbedo(const float r, const float g, const float b) noexcept
	{
		setAlbedo({ r, g, b });
	}

	constexpr float LightBaseComponent::getAmbientStrength() const noexcept
	{
		return __ambientStrength;
	}

	constexpr void LightBaseComponent::setAmbientStrength(const float strength) noexcept
	{
		__ambientStrength = strength;
	}

	constexpr float LightBaseComponent::getDiffuseStrength() const noexcept
	{
		return __diffuseStrength;
	}

	constexpr void LightBaseComponent::setDiffuseStrength(const float strength) noexcept
	{
		__diffuseStrength = strength;
	}

	constexpr float LightBaseComponent::getSpecularStrength() const noexcept
	{
		return __specularStrength;
	}

	constexpr void LightBaseComponent::setSpecularStrength(const float strength) noexcept
	{
		__specularStrength = strength;
	}
}