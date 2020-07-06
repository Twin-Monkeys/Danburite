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
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		GammaCorrectionPostProcessor();

		constexpr void setGamma(const float gamma) noexcept;

		virtual ~GammaCorrectionPostProcessor() = default;
	};

	constexpr void GammaCorrectionPostProcessor::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
	}
}