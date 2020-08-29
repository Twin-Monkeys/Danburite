#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class ConvolutionUniformInterface : public UniformInterface<
		(sizeof(GLfloat) * Constant::Convolutional::MAX_KERNEL_SIZE_SQ) + 4ULL>
	{
	public:
		// 4byte 2D array
		const SpecializedUniformFieldArray<GLfloat, Constant::Convolutional::MAX_KERNEL_SIZE_SQ>
			kernel = _createFieldArray<GLfloat, Constant::Convolutional::MAX_KERNEL_SIZE_SQ>(0);

		// 4byte
		const SpecializedUniformField<GLuint> kernelSize =
			_createField<GLuint>(sizeof(GLfloat) * Constant::Convolutional::MAX_KERNEL_SIZE_SQ);

		ConvolutionUniformInterface() noexcept;
		virtual ~ConvolutionUniformInterface() = default;
	};
}
