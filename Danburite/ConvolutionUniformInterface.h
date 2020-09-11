#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class ConvolutionUniformInterface : public UniformInterface<
		(16ULL * Constant::Convolutional::MAX_KERNEL_SIZE_SQ) + 16ULL>
	{
	public:
		const SpecializedUniformFieldArray<GLfloat, Constant::Convolutional::MAX_KERNEL_SIZE_SQ>
			kernel = _createFieldArray<GLfloat, Constant::Convolutional::MAX_KERNEL_SIZE_SQ>(0);

		const SpecializedUniformField<GLuint> kernelSize =
			_createField<GLuint>(16ULL * Constant::Convolutional::MAX_KERNEL_SIZE_SQ);

		ConvolutionUniformInterface() noexcept;
		virtual ~ConvolutionUniformInterface() = default;
	};
}
