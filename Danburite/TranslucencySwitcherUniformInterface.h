#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class TranslucencySwitcherUniformInterface : public UniformInterface<4ULL>
	{
	public:
		const SpecializedUniformField<GLuint> mode = _createField<GLuint>(0);

		TranslucencySwitcherUniformInterface() noexcept;
		virtual ~TranslucencySwitcherUniformInterface() = default;
	};
}
