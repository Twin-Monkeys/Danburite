#pragma once

#include "ForwardPostProcessor.h"
#include "ShaderIdentifier.h"
#include <array>

namespace Danburite
{
	namespace ConvValue = ShaderIdentifier::Value::Convolutional;

	class ConvolutionalPostProcessor : public ForwardPostProcessor
	{
	private:
		ObjectGL::UniformSetter &__convSetter;
		GLuint __kernelSize = 3U;

		std::array<GLfloat, ConvValue::MAX_KERNEL_SIZE * ConvValue::MAX_KERNEL_SIZE> __kernel =
		{
			0.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 0.f
		};

		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		ConvolutionalPostProcessor(const bool attachDepthBuffer = false);

		void setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept;

		virtual ~ConvolutionalPostProcessor() = default;
	};
}