#pragma once

#include "ForwardPostProcessor.h"
#include "Constant.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class HDRPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformBuffer &__hdrSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::HDR);

		float __exposure = Constant::HDR::DEFAULT_EXPOSURE;

		SetupTransaction __setupTransaction;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		HDRPostProcessor(const bool attachDepthBuffer = false);

		constexpr float getExposure() const noexcept;
		constexpr void setExposure(const float exposure) noexcept;

		virtual ~HDRPostProcessor() = default;
	};

	constexpr float HDRPostProcessor::getExposure() const noexcept
	{
		return __exposure;
	}

	constexpr void HDRPostProcessor::setExposure(const float exposure) noexcept
	{
		__exposure = exposure;
	}
}