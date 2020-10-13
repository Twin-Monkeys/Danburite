#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class FXAAUniformInterface : public UniformInterface<(16ULL * Constant::FXAA::MAX_NUM_EDGE_STEPS) + 64ULL>
	{
	public:
		const SpecializedUniformFieldArray<
			GLfloat, Constant::FXAA::MAX_NUM_EDGE_STEPS>
			edgeSteps = _createFieldArray<GLfloat, Constant::FXAA::MAX_NUM_EDGE_STEPS>
			(0ULL);

		const SpecializedUniformField<GLuint> numEdgeSteps =
			_createField<GLuint>
			(16ULL * Constant::FXAA::MAX_NUM_EDGE_STEPS);

		const SpecializedUniformField<GLfloat> absoluteThreshold =
			_createField<GLfloat>
			((16ULL * Constant::FXAA::MAX_NUM_EDGE_STEPS) + 16ULL);

		const SpecializedUniformField<GLfloat> relativeThreshold =
			_createField<GLfloat>
			((16ULL * Constant::FXAA::MAX_NUM_EDGE_STEPS) + 32ULL);

		const SpecializedUniformField<GLfloat> subpixelBlendingFactor =
			_createField<GLfloat>
			((16ULL * Constant::FXAA::MAX_NUM_EDGE_STEPS) + 48ULL);

		FXAAUniformInterface() noexcept;
		virtual ~FXAAUniformInterface() = default;
	};
}
