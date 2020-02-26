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
#include "MaterialRenderType.h"

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

		constexpr void __setOption(const MaterialOptionFlag flags, const bool enabled) noexcept;

		static void __render_normal(
			Material &instance, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept;

		static void __render_depthBaking(
			Material &instance, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept;

		static inline void (*__pRenderFunc)(
			Material &instance, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) = &__render_normal;

	protected:
		Material(
			const std::unordered_set<ProgramType> &programTypes,
			const MaterialType materialType, const VertexAttributeType vertexType) noexcept;

		virtual void _onRender(MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept = 0;

		constexpr void useLighting(const bool enabled) noexcept;
		constexpr void useAmbientTexture(const bool enabled) noexcept;
		constexpr void useSpecularTexture(const bool enabled) noexcept;
		constexpr void useShininessTexture(const bool enabled) noexcept;
		constexpr void useAlphaTexture(const bool enabled) noexcept;
		constexpr void useNormalTexture(const bool enabled) noexcept;

	public:
		static constexpr void setGamma(const float gamma) noexcept;
		static constexpr void setRenderType(const MaterialRenderType type) noexcept;

		void render(ObjectGL::VertexArray &vertexArray, const GLsizei numInstances = 1) noexcept;

		virtual ~Material() = default;
	};

	constexpr void Material::__setOption(const MaterialOptionFlag flags, const bool enabled) noexcept
	{
		if (enabled)
			__optionFlag |= flags;
		else
			__optionFlag &= ~flags;
	}

	constexpr void Material::useLighting(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::LIGHTING, enabled);
	}

	constexpr void Material::useAmbientTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::AMBIENT_TEXTURE, enabled);
	}

	constexpr void Material::useSpecularTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SPECULAR_TEXTURE, enabled);
	}

	constexpr void Material::useShininessTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SHININESS_TEXTURE, enabled);
	}

	constexpr void Material::useAlphaTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::ALPHA_TEXTURE, enabled);
	}

	constexpr void Material::useNormalTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::NORMAL_TEXTURE, enabled);
	}

	constexpr void Material::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
	}

	constexpr void Material::setRenderType(const MaterialRenderType type) noexcept
	{
		switch (type)
		{
		case MaterialRenderType::NORMAL:
			__pRenderFunc = &__render_normal;
			break;

		case MaterialRenderType::DEPTH_BAKING:
			__pRenderFunc = &__render_depthBaking;
			break;
		}
	}
}
