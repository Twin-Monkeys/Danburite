#pragma once

#include "ForwardPostProcessor.h"
#include "UniformBufferFactory.h"
#include "FXAAUniformInterface.h"

namespace Danburite
{
	class FXAAPostProcessor : public ForwardPostProcessor
	{
	private:
		DeferredUniformBuffer<FXAAUniformInterface> &__fxaaUB =
			UniformBufferFactory::getInstance().getUniformBuffer<FXAAUniformInterface>();

		unsigned __numEdgeSteps;
		float __edgeSteps[Constant::FXAA::MAX_NUM_EDGE_STEPS];

		/*
			Trims the algorithm from processing darks.
			0.0833 - upper limit (default, the start of visible unfiltered edges)
			0.0625 - high quality (faster)
			0.0312 - visible limit (slower)
		*/
		float __absoluteThreshold = Constant::FXAA::DEFAULT_ABSOLUTE_THRESHOLD;

		/*
			The minimum amount of local contrast required to apply algorithm.
			0.333 - too little (faster)
			0.250 - low quality
			0.166 - default
			0.125 - high quality
			0.063 - overkill (slower)
		*/
		float __relativeThreshold = Constant::FXAA::DEFAULT_RELATIVE_THRESHOLD;

		/*
			Choose the amount of sub-pixel aliasing removal.
			This can effect sharpness.
			1.00 - upper limit (softer)
			0.75 - default amount of filtering
			0.50 - lower limit (sharper, less sub-pixel aliasing removal)
			0.25 - almost off
			0.00 - completely off
		*/
		float __subpixelBlendingFactor = Constant::FXAA::DEFAULT_SUBPIXEL_BLENDING_FACTOR;

		SetupTransaction __setup;

	public:
		FXAAPostProcessor(const bool attachDepthBuffer = false);
		virtual ~FXAAPostProcessor() = default;

		void setEdgeSteps(const float *const pEdgeSteps, const size_t numEdgeStep) noexcept;
		constexpr void setAbsoluteThreshold(const float absoluteThreshold) noexcept;
		constexpr void setRelativeThreshold(const float relativeThreshold) noexcept;
		constexpr void setSubpixelBlendingFactor(const float subpixelBlendingFactor) noexcept;

		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;
	};

	constexpr void FXAAPostProcessor::setAbsoluteThreshold(const float absoluteThreshold) noexcept
	{
		__absoluteThreshold = absoluteThreshold;
	}

	constexpr void FXAAPostProcessor::setRelativeThreshold(const float relativeThreshold) noexcept
	{
		__relativeThreshold = relativeThreshold;
	}

	constexpr void FXAAPostProcessor::setSubpixelBlendingFactor(const float subpixelBlendingFactor) noexcept
	{
		__subpixelBlendingFactor = subpixelBlendingFactor;
	}
}