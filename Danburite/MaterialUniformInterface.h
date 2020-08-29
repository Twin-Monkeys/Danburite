#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class MaterialUniformInterface : public UniformInterface
	{
	public:
		// 16byte
		const UniformField<glm::vec4> diffuseColor		= _createField<glm::vec4>();

		// 8byte
		const UniformField<GLuint64> ambientTex			= _createField<GLuint64>();
		const UniformField<GLuint64> diffuseTex			= _createField<GLuint64>();
		const UniformField<GLuint64> specularTex		= _createField<GLuint64>();
		const UniformField<GLuint64> emissiveTex		= _createField<GLuint64>();
		const UniformField<GLuint64> shininessTex		= _createField<GLuint64>();
		const UniformField<GLuint64> alphaTex			= _createField<GLuint64>();
		const UniformField<GLuint64> normalTex			= _createField<GLuint64>();
		const UniformField<GLuint64> heightTex			= _createField<GLuint64>();
		const UniformField<GLuint64> environmentTex		= _createField<GLuint64>();

		// 4byte
		const UniformField<GLuint> type					= _createField<GLuint>();
		const UniformField<GLuint> optionFlag			= _createField<GLuint>();
		const UniformField<GLuint> vertexFlag			= _createField<GLuint>();
		const UniformField<GLfloat> gamma				= _createField<GLfloat>();
		const UniformField<GLfloat> emissiveStrength	= _createField<GLfloat>();
		const UniformField<GLfloat> shininess			= _createField<GLfloat>();
		const UniformField<GLfloat> overriddenAlpha		= _createField<GLfloat>();

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
