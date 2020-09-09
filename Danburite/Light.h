#pragma once

#include "Object.h"
#include "LightType.h"
#include "LightVolumeType.h"
#include "LightException.h"
#include "BatchProcessor.h"
#include "DepthBakingType.h"
#include "UniformBuffer.h"
#include "SceneObject.h"
#include "UniformBufferFactory.h"
#include "LightUniformInterface.h"
#include "LightPrePassUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class Light abstract
	{
	private:
		const GLuint __TYPE;
		const GLuint __VOLUME_TYPE;
		const GLuint __DEPTH_BAKING_TYPE;
		GLuint __index;

		bool __enabled = true;
		bool __shadowEnabled = false;

		DeferredUniformBuffer<LightUniformInterface> &__lightUB =
			UniformBufferFactory::getInstance().getUniformBuffer<LightUniformInterface>();

		DeferredUniformBuffer<LightPrePassUniformInterface> &__lightPrepassUB =
			UniformBufferFactory::getInstance().getUniformBuffer<LightPrePassUniformInterface>();

		void __release() noexcept;
		
	protected:
		virtual void _onDeploy(LightUniformInterface &lightUI) noexcept = 0;
		virtual void _onBakeDepthMap(BatchProcessor<SceneObject> &drawer) noexcept = 0;
		virtual void _onDeployShadowData(LightUniformInterface &lightUI) noexcept = 0;
		virtual void _onVolumeDrawcall() noexcept = 0;
		virtual void _onChangeShadowEnabled(const bool enabled) noexcept = 0;

	public:
		Light(
			const LightType type, const LightVolumeType volumeType,
			const DepthBakingType depthBakingType, const GLuint index);

		void selfDeploy() noexcept;

		constexpr GLuint getIndex() const noexcept;
		constexpr void setIndex(const GLuint index) noexcept;

		constexpr bool isEnabled() const noexcept;
		constexpr void setEnabled(const bool enabled) noexcept;

		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept = 0;
		virtual const glm::ivec2 &getDepthMapSize() noexcept = 0;

		constexpr bool isShadowEnabled() const noexcept;
		void setShadowEnabled(const bool enabled) noexcept;

		void bakeDepthMap(BatchProcessor<SceneObject> &drawer) noexcept;

		void volumeDrawcall() noexcept;

		virtual ~Light() noexcept;
	};

	constexpr GLuint Light::getIndex() const noexcept
	{
		return __index;
	}

	constexpr void Light::setIndex(const GLuint index) noexcept
	{
		__index = index;
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
}