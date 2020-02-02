#pragma once

#include "MaterialUniformDeployable.h"
#include <memory>
#include "Texture2D.h"
#include "MaterialType.h"
#include <unordered_set>
#include "MaterialOptionFlag.h"
#include "VertexArray.h"
#include "VertexAttributeType.h"
#include "Constant.h"

namespace Danburite
{
	class Material abstract : virtual public MaterialUniformDeployable
	{
	private:
		MaterialUniformSetter __materialUniformSetter;

		const MaterialType __MATERIAL_TYPE;
		const VertexAttributeType __VERTEX_TYPE;

		MaterialOptionFlag __optionFlag = MaterialOptionFlag::NONE;
		static inline float __gamma = 1.f;

		void __setOption(const MaterialOptionFlag flags, const bool enabled) noexcept;

	protected:
		Material(
			const std::unordered_set<ProgramType> &programTypes,
			const MaterialType materialType, const VertexAttributeType vertexType) noexcept;

		virtual void _onRender(MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept = 0;

		void useLighting(const bool enabled) noexcept;
		void useAmbientTexture(const bool enabled) noexcept;
		void useSpecularTexture(const bool enabled) noexcept;
		void useShininessTexture(const bool enabled) noexcept;
		void useAlphaTexture(const bool enabled) noexcept;
		void useNormalTexture(const bool enabled) noexcept;

	public:
		static void setGamma(const float gamma) noexcept;

		void render(ObjectGL::VertexArray &vertexArray, const GLsizei numInstances = 1) noexcept;

		virtual ~Material() = default;
	};
}
