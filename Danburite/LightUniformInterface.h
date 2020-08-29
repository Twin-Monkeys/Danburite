#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightUniformInterface : public UniformInterface<
		(164 * Constant::Light::MAX_NUM_LIGHTS) + 4ULL>
	{
	public:
		// 64byte array
		const SpecializedUniformFieldArray<glm::mat4, Constant::Light::MAX_NUM_LIGHTS>
			projViewMat = _createFieldArray<glm::mat4, Constant::Light::MAX_NUM_LIGHTS>
			(0);


		// for align
		const SpecializedUniformFieldArray<GLuint64, Constant::Light::MAX_NUM_LIGHTS>
			depthMap = _createFieldArray<GLuint64, Constant::Light::MAX_NUM_LIGHTS>
			(64 * Constant::Light::MAX_NUM_LIGHTS);


		// 12byte array
		const SpecializedUniformFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			direction = _createFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			(72 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			pos = _createFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			(84 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			albedo = _createFieldArray<glm::vec3, Constant::Light::MAX_NUM_LIGHTS>
			(96 * Constant::Light::MAX_NUM_LIGHTS);


		// 4byte array
		const SpecializedUniformFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			enabled = _createFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			(108 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			shadowEnabled = _createFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			(112 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			type = _createFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			(116 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			depthBakingType = _createFieldArray<GLuint, Constant::Light::MAX_NUM_LIGHTS>
			(120 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			ambientStrength	= _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(124 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			diffuseStrength	= _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(128 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			specularStrength = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(132 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			attConst = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(136 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			attLinear = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(140 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			attQuad = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(144 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			validDistance = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(148 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			innerCutOff = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(152 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			outerCutOff = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(156 * Constant::Light::MAX_NUM_LIGHTS);

		const SpecializedUniformFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			zFar = _createFieldArray<GLfloat, Constant::Light::MAX_NUM_LIGHTS>
			(160 * Constant::Light::MAX_NUM_LIGHTS);


		// 4byte
		const SpecializedUniformField<GLuint> numLights =
			_createField<GLuint>(164 * Constant::Light::MAX_NUM_LIGHTS);

		LightUniformInterface() noexcept;
		virtual ~LightUniformInterface() = default;
	};
}
