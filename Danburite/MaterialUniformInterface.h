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
		const UniformField<glm::vec4> diffuseColor		= _appendField<glm::vec4>();

		// 8byte
		const UniformField<GLuint64> ambientTex			= _appendField<GLuint64>();
		const UniformField<GLuint64> diffuseTex			= _appendField<GLuint64>();
		const UniformField<GLuint64> specularTex		= _appendField<GLuint64>();
		const UniformField<GLuint64> emissiveTex		= _appendField<GLuint64>();
		const UniformField<GLuint64> shininessTex		= _appendField<GLuint64>();
		const UniformField<GLuint64> alphaTex			= _appendField<GLuint64>();
		const UniformField<GLuint64> normalTex			= _appendField<GLuint64>();
		const UniformField<GLuint64> heightTex			= _appendField<GLuint64>();
		const UniformField<GLuint64> environmentTex		= _appendField<GLuint64>();

		// 4byte
		const UniformField<GLuint> type					= _appendField<GLuint>();
		const UniformField<GLuint> optionFlag			= _appendField<GLuint>();
		const UniformField<GLuint> vertexFlag			= _appendField<GLuint>();
		const UniformField<GLfloat> gamma				= _appendField<GLfloat>();
		const UniformField<GLfloat> emissiveStrength	= _appendField<GLfloat>();
		const UniformField<GLfloat> shininess			= _appendField<GLfloat>();
		const UniformField<GLfloat> overriddenAlpha		= _appendField<GLfloat>();

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
