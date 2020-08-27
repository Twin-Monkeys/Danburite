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
		const UniformField<glm::uvec2> ambientTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> diffuseTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> specularTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> emissiveTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> shininessTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> alphaTex			= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> normalTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> heightTex		= _appendField<glm::uvec2>();
		const UniformField<glm::uvec2> environmentTex	= _appendField<glm::uvec2>();

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
