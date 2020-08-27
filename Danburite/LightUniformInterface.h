#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightUniformInterface : public UniformInterface
	{
	public:
		// 64byte array
		const UniformField<glm::mat4[Constant::Light::MAX_NUM_LIGHTS]> projViewMat		= _appendField<glm::mat4[Constant::Light::MAX_NUM_LIGHTS]>();

		// for align
		const UniformField<glm::uvec2[Constant::Light::MAX_NUM_LIGHTS]> depthMap		= _appendField<glm::uvec2[Constant::Light::MAX_NUM_LIGHTS]>();

		// 12byte array
		const UniformField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]> direction		= _appendField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]> pos				= _appendField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]> albedo			= _appendField<glm::vec3[Constant::Light::MAX_NUM_LIGHTS]>();

		// 4byte array
		const UniformField<GLuint[Constant::Light::MAX_NUM_LIGHTS]> enabled				= _appendField<GLuint[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLuint[Constant::Light::MAX_NUM_LIGHTS]> shadowEnabled		= _appendField<GLuint[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLuint[Constant::Light::MAX_NUM_LIGHTS]> type				= _appendField<GLuint[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLuint[Constant::Light::MAX_NUM_LIGHTS]> depthBakingType		= _appendField<GLuint[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> ambientStrength	= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> diffuseStrength	= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> specularStrength	= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> attConst			= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> attLinear			= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> attQuad			= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> validDistance		= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> innerCutOff		= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> outerCutOff		= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();
		const UniformField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]> zFar				= _appendField<GLfloat[Constant::Light::MAX_NUM_LIGHTS]>();

		// 4byte
		const UniformField<GLuint> numLights											= _appendField<GLuint>();

		LightUniformInterface() noexcept;
		virtual ~LightUniformInterface() = default;
	};
}
