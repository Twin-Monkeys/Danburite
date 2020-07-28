#pragma once

#include "PostProcessor.h"
#include "AttachableTextureRectangle.h"
#include "RenderBuffer.h"
#include "Constant.h"

namespace Danburite
{
	class BloomPostProcessor : public PostProcessor
	{
	private:
		const bool __attachDepthBuffer;

		ObjectGL::UniformBuffer &__bloomSetter;

		float __brightnessThreshold =
			Constant::Bloom::DEFAULT_BRIGHTNESS_THRESHOLD;

		float __effectStrength =
			Constant::Bloom::DEFAULT_EFFECT_STRENGTH;

		ObjectGL::Program &__extractionProgram;
		ObjectGL::Program &__blurHorizProgram;
		ObjectGL::Program &__blurVertProgram;
		ObjectGL::Program &__compositionProgram;

		std::unique_ptr<ObjectGL::FrameBuffer> __pBloomFrameBuffer1;
		std::unique_ptr<ObjectGL::FrameBuffer> __pBloomFrameBuffer2;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pOriginalColorAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pBloomColorAttachment1;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pBloomColorAttachment2;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		virtual void _onRender(
			PostProcessor* const pBoundProcessor,
			ObjectGL::UniformBuffer &texContainerSetter,
			FullscreenDrawer &fullscreenDrawer) noexcept override;

	public:
		BloomPostProcessor(const bool attachDepthBuffer = false);

		constexpr float getBrightnessThreshold() const noexcept;
		constexpr void setBrightnessThreshold(const float threshold) noexcept;

		constexpr float getEffectStrength() const noexcept;
		constexpr void setEffectStrength(const float strength) noexcept;

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~BloomPostProcessor() = default;
	};

	constexpr float BloomPostProcessor::getBrightnessThreshold() const noexcept
	{
		return __brightnessThreshold;
	}

	constexpr void BloomPostProcessor::setBrightnessThreshold(const float threshold) noexcept
	{
		__brightnessThreshold = threshold;
	}

	constexpr float BloomPostProcessor::getEffectStrength() const noexcept
	{
		return __effectStrength;
	}

	constexpr void BloomPostProcessor::setEffectStrength(const float strength) noexcept
	{
		__effectStrength = strength;
	}
}