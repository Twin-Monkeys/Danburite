#pragma once

#include "ForwardPostProcessor.h"
#include "UniformBufferFactory.h"
#include "ConvolutionUniformInterface.h"
#include "Constant.h"
#include <array>

namespace Danburite
{
	class ConvolutionalPostProcessor : public ForwardPostProcessor
	{
	private:
		DeferredUniformBuffer<ConvolutionUniformInterface> &__convUB =
			UniformBufferFactory::getInstance().getUniformBuffer<ConvolutionUniformInterface>();

		GLuint __kernelSize = 3U;

		std::array<GLfloat, Constant::Convolutional::MAX_KERNEL_SIZE_SQ> __kernel =
		{
			0.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 0.f
		};

		SetupTransaction __setupTransaction;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		ConvolutionalPostProcessor(const bool attachDepthBuffer = false);

		void setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept;

		virtual ~ConvolutionalPostProcessor() = default;
	};
}