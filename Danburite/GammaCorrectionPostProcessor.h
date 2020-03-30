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
			ObjectGL::UniformSetter &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		GammaCorrectionPostProcessor();

		void setGamma(const float gamma) noexcept;

		virtual ~GammaCorrectionPostProcessor() = default;
	};
}