#pragma once

#include "Object.h"
#include "LightUniformSetter.h"
#include "LightType.h"
#include "LightException.h"
#include "BatchProcessor.h"
#include "DepthBakingType.h"
#include "UniformBuffer.h"
#include "Drawable.h"

namespace Danburite
{
	class Light abstract
	{
	private:
		const GLenum __TYPE;
		const GLenum __DEPTH_BAKING_TYPE;

		bool __enabled = true;
		bool __shadowEnabled = false;

		LightUniformSetter __lightSetter;
		ObjectGL::UniformBuffer &__lightPrePassSetter;

		void __release() noexcept;
		
	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept = 0;
		virtual void _onBakeDepthMap(BatchProcessor<Drawable> &drawer) noexcept = 0;
		virtual void _onDeployShadowData(LightUniformSetter &lightSetter) noexcept = 0;
		virtual void _onVolumeDrawcall() noexcept = 0;

	public:
		Light(const LightType type, const DepthBakingType depthBakingType, const GLuint index);

		void selfDeploy() noexcept;

		constexpr GLuint getIndex() const noexcept;
		void setIndex(const GLuint index) noexcept;

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		constexpr bool isShadowEnabled() const noexcept;
		constexpr void setShadowEnabled(const bool enabled) noexcept;

		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept = 0;
		void bakeDepthMap(BatchProcessor<Drawable> &drawer) noexcept;

		void volumeDrawcall() noexcept;

		virtual ~Light() noexcept;
	};

	constexpr GLuint Light::getIndex() const noexcept
	{
		return __lightSetter.getIndex();
	}

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