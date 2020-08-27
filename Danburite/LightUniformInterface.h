#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class MaterialUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint> type;
		const UniformField<GLuint> optionFlag;
		const UniformField<GLuint> vertexFlag;
		const UniformField<glm::vec4> diffuseColor;
		const UniformField<GLfloat> gamma;
		const UniformField<GLfloat> emissiveStrength;
		const UniformField<GLfloat> shininess;
		const UniformField<glm::uvec2> ambientTex;
		const UniformField<glm::uvec2> diffuseTex;
		const UniformField<glm::uvec2> specularTex;
		const UniformField<glm::uvec2> emissiveTex;
		const UniformField<glm::uvec2> shininessTex;
		const UniformField<glm::uvec2> alphaTex;
		const UniformField<glm::uvec2> normalTex;
		const UniformField<glm::uvec2> heightTex;
		const UniformField<glm::uvec2> environmentTex;
		const UniformField<GLfloat> overriddenAlpha;

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
