#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class ConvolutionUniformInterface : public UniformInterface
	{
	public:
		// 4byte 2D array
		const UniformField<GLfloat[Constant::Convolutional::MAX_KERNEL_SIZE][Constant::Convolutional::MAX_KERNEL_SIZE]> kernel =
			_appendField<GLfloat[Constant::Convolutional::MAX_KERNEL_SIZE][Constant::Convolutional::MAX_KERNEL_SIZE]>();

		// 4byte
		const UniformField<GLuint> kernelSize = _appendField<GLuint>();

		ConvolutionUniformInterface() noexcept;
		virtual ~ConvolutionUniformInterface() = default;
	};
}
