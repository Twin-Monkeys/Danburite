#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class MaterialUniformInterface : public UniformInterface<288ULL>
	{
	public:
		const SpecializedUniformField<glm::vec4> diffuseColor	= _createField<glm::vec4>(0ULL);
		const SpecializedUniformField<GLuint64> ambientTex		= _createField<GLuint64>(16ULL);
		const SpecializedUniformField<GLuint64> diffuseTex		= _createField<GLuint64>(32ULL);
		const SpecializedUniformField<GLuint64> specularTex		= _createField<GLuint64>(48ULL);
		const SpecializedUniformField<GLuint64> emissiveTex		= _createField<GLuint64>(64ULL);
		const SpecializedUniformField<GLuint64> shininessTex	= _createField<GLuint64>(80ULL);
		const SpecializedUniformField<GLuint64> alphaTex		= _createField<GLuint64>(96ULL);
		const SpecializedUniformField<GLuint64> normalTex		= _createField<GLuint64>(112ULL);
		const SpecializedUniformField<GLuint64> heightTex		= _createField<GLuint64>(128ULL);
		const SpecializedUniformField<GLuint64> occlusionTex	= _createField<GLuint64>(144ULL);
		const SpecializedUniformField<GLuint64> environmentTex	= _createField<GLuint64>(160ULL);
		const SpecializedUniformField<GLuint> type				= _createField<GLuint>(176ULL);
		const SpecializedUniformField<GLuint> optionFlag		= _createField<GLuint>(192ULL);
		const SpecializedUniformField<GLuint> vertexFlag		= _createField<GLuint>(208ULL);
		const SpecializedUniformField<GLfloat> gamma			= _createField<GLfloat>(224ULL);
		const SpecializedUniformField<GLfloat> emissiveStrength	= _createField<GLfloat>(240ULL);
		const SpecializedUniformField<GLfloat> shininess		= _createField<GLfloat>(256ULL);
		const SpecializedUniformField<GLfloat> overriddenAlpha	= _createField<GLfloat>(272ULL);

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
