#pragma once

#include "ForwardPostProcessor.h"
#include "Constant.h"

namespace Danburite
{
	class GammaCorrectionPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformSetter &__paramSetter;

		float __gamma = Constant::GammaCorrection::DEFAULT_GAMMA;

	protected:
		virtual void _onRender() noexcept override;

	public:
		GammaCorrectionPostProcessor(ObjectGL::UniformSetter &parameterSetter);

		void setGamma(const float gamma) noexcept;

		virtual ~GammaCorrectionPostProcessor() = default;
	};
}