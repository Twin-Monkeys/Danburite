#pragma once

#include "Object.h"
#include "LightUniformDeployable.h"
#include <array>
#include "ShaderIdentifier.h"
#include "LightUniformSetter.h"
#include "LightType.h"
#include "LightException.h"
#include "DepthBaker.h"
#include "Drawer.h"

namespace Danburite
{
	class Light abstract : public ObjectGL::Object<glm::uint>, virtual public LightUniformDeployable
	{
	private:
		class LightIDAllocator
		{
		private:
			std::array<bool, ShaderIdentifier::Value::Light::MAX_NUM_LIGHTS> __occupationMap { false };

		public:
			glm::uint allocate();
			void deallocate(const glm::uint id) noexcept;
		};

		bool __enabled = true;
		bool __shadowEnabled = false;

		LightUniformSetter __lightParamSetter;
		DepthBaker __depthBaker;

		void __release() noexcept;
		
		constexpr static LightIDAllocator &__getAllocator() noexcept;

	protected:
		virtual const glm::mat4 &_getViewMatrix() const noexcept = 0;
		virtual const glm::mat4 &_getProjMatrix() const noexcept = 0;

	public:
		Light(const LightType type);

		void selfDeploy() noexcept;

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		constexpr bool isShadowEnabled() const noexcept;
		constexpr void setShadowEnabled(const bool enabled) noexcept;

		void setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept;

		void startDepthBaking() noexcept;
		void endDepthBaking() noexcept;
		void bakeDepthMap(Drawer &drawer, const bool cancelIfShadowDisabled = true) noexcept;

		virtual ~Light() noexcept;
	};

	constexpr bool Light::isEnabled() const noexcept
	{
		return __enabled;
	}

	constexpr void Light::setEnabled(const bool enabled) noexcept
	{
		__enabled = enabled;
	}

	constexpr bool Light::isShadowEnabled() const noexcept
	{
		return __shadowEnabled;
	}

	constexpr void Light::setShadowEnabled(const bool enabled) noexcept
	{
		__shadowEnabled = enabled;
	}
}