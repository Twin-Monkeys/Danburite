#pragma once

#include "Object.h"
#include "LightUniformDeployable.h"
#include <array>
#include "ShaderIdentifier.h"
#include "LightUniformSetter.h"
#include "LightType.h"
#include "LightException.h"
#include "Drawer.h"
#include "DepthBakingType.h"
#include "UniformBuffer.h"

namespace Danburite
{
	class Light abstract : public ObjectGL::Object<glm::uint>, protected LightUniformDeployable
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

		LightUniformSetter __lightSetter;
		ObjectGL::UniformBuffer &__lightPrePassSetter;

		void __release() noexcept;
		
		static LightIDAllocator &__getAllocator() noexcept;

	protected:
		virtual void _onBakeDepthMap(Drawer &drawer) noexcept = 0;
		virtual void _onDeployShadowData(LightUniformSetter &lightSetter) noexcept = 0;
		virtual void _onVolumeDrawcall() noexcept = 0;

	public:
		Light(const LightType type, const DepthBakingType depthBakingType);

		void selfDeploy() noexcept;

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		constexpr bool isShadowEnabled() const noexcept;
		constexpr void setShadowEnabled(const bool enabled) noexcept;

		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept = 0;
		void bakeDepthMap(Drawer &drawer) noexcept;

		void volumeDrawcall() noexcept;

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