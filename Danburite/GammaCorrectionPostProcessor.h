#pragma once

#include "ForwardPostProcessor.h"
#include "UniformBufferFactory.h"
#include "MaterialUniformInterface.h"
#include "GammaCorrectionUniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class GammaCorrectionPostProcessor : public ForwardPostProcessor
	{
	private:
		DeferredUniformBuffer<MaterialUniformInterface> &__materialUB =
			UniformBufferFactory::getInstance().getUniformBuffer<MaterialUniformInterface>();

		DeferredUniformBuffer<GammaCorrectionUniformInterface> &__gammaCorrectionUB =
			UniformBufferFactory::getInstance().getUniformBuffer<GammaCorrectionUniformInterface>();

		float __gamma = Constant::GammaCorrection::DEFAULT_GAMMA;

		SetupTransaction __setupTransaction;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

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