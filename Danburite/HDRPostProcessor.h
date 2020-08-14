#pragma once

#include "ForwardPostProcessor.h"
#include "Constant.h"

namespace Danburite
{
	class HDRPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformBuffer &__hdrSetter;
		float __exposure = Constant::HDR::DEFAULT_EXPOSURE;

	protected:
		virtual void _onRender(
			ObjectGL::FrameBuffer &renderTarget,
			ObjectGL::UniformBuffer &texContainerSetter,
			FullscreenDrawer &fullscreenDrawer) noexcept override;

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