#pragma once

#include "PostProcessor.h"
#include "AttachableTexture2D.h"
#include "RenderBuffer.h"
#include "Constant.h"

namespace Danburite
{
	class BloomPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::UniformBuffer &__bloomSetter;

		float __brightnessThreshold =
			Constant::Bloom::DEFAULT_BRIGHTNESS_THRESHOLD;

		ObjectGL::Program &__extractionProgram;
		ObjectGL::Program &__blurHorizProgram;
		ObjectGL::Program &__blurVertProgram;
		ObjectGL::Program &__compositionProgram;

		std::unique_ptr<ObjectGL::FrameBuffer> __pBloomFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pOriginalColorAttachment;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pBloomColorAttachment1;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pBloomColorAttachment2;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		void __initColorAttachment() noexcept;

	protected:
		virtual void _onRender(
			ObjectGL::UniformBuffer& attachmentSetter, ObjectGL::VertexArray& fullscreenQuadVA) noexcept override;

	public:
		BloomPostProcessor(const bool attachDepthBuffer = false);

		constexpr float getBrightnessThreshold() const noexcept;
		constexpr void setBrightnessThreshold(const float threshold) noexcept;

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
}