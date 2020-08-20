#pragma once

#include "ForwardPostProcessor.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class GammaCorrectionPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformSetter& __materialSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL);

		ObjectGL::UniformSetter &__gammaCorrectionSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION);

		float __gamma;

		SetupTransaction __setupTransaction;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		GammaCorrectionPostProcessor(const bool attachDepthBuffer = false);
		void setGamma(const float gamma) noexcept;

		virtual ~GammaCorrectionPostProcessor() = default;
	};
}