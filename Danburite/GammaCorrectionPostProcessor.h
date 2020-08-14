#pragma once

#include "ForwardPostProcessor.h"
#include "Constant.h"

namespace Danburite
{
	class GammaCorrectionPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformSetter &__gammaCorrectionSetter;
		float __gamma = Constant::GammaCorrection::DEFAULT_GAMMA;

	protected:
		virtual void _onRender(
			ObjectGL::FrameBuffer &renderTarget,
			ObjectGL::UniformBuffer &texContainerSetter,
			FullscreenDrawer &fullscreenDrawer) noexcept override;

	public:
		GammaCorrectionPostProcessor(const bool attachDepthBuffer = false);

		constexpr void setGamma(const float gamma) noexcept;

		virtual ~GammaCorrectionPostProcessor() = default;
	};

	constexpr void GammaCorrectionPostProcessor::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
	}
}