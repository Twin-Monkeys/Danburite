#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class MaterialUniformInterface : public UniformInterface<116ULL>
	{
	public:
		// 16byte
		const SpecializedUniformField<glm::vec4> diffuseColor = _createField<glm::vec4>(0ULL);

		// 8byte
		const SpecializedUniformField<GLuint64> ambientTex = _createField<GLuint64>(16ULL);
		const SpecializedUniformField<GLuint64> diffuseTex = _createField<GLuint64>(24ULL);
		const SpecializedUniformField<GLuint64> specularTex = _createField<GLuint64>(32ULL);
		const SpecializedUniformField<GLuint64> emissiveTex = _createField<GLuint64>(40ULL);
		const SpecializedUniformField<GLuint64> shininessTex = _createField<GLuint64>(48ULL);
		const SpecializedUniformField<GLuint64> alphaTex = _createField<GLuint64>(56ULL);
		const SpecializedUniformField<GLuint64> normalTex = _createField<GLuint64>(64ULL);
		const SpecializedUniformField<GLuint64> heightTex = _createField<GLuint64>(72ULL);
		const SpecializedUniformField<GLuint64> environmentTex = _createField<GLuint64>(80ULL);

		// 4byte
		const SpecializedUniformField<GLuint> type = _createField<GLuint>(88ULL);
		const SpecializedUniformField<GLuint> optionFlag = _createField<GLuint>(92ULL);
		const SpecializedUniformField<GLuint> vertexFlag = _createField<GLuint>(96ULL);
		const SpecializedUniformField<GLfloat> gamma = _createField<GLfloat>(100ULL);
		const SpecializedUniformField<GLfloat> emissiveStrength = _createField<GLfloat>(104ULL);
		const SpecializedUniformField<GLfloat> shininess = _createField<GLfloat>(108ULL);
		const SpecializedUniformField<GLfloat> overriddenAlpha = _createField<GLfloat>(112ULL);

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
