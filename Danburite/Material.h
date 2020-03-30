#pragma once

#include <memory>
#include "MaterialType.h"
#include "MaterialOptionFlag.h"
#include "VertexArray.h"
#include "VertexAttributeType.h"
#include "Constant.h"
#include "MaterialRenderType.h"
#include "UniformSetter.h"

namespace Danburite
{
	class Material abstract
	{
	private:
		const MaterialType __MATERIAL_TYPE;
		const VertexAttributeType __VERTEX_TYPE;

		ObjectGL::UniformSetter &__uniformSetter;

		MaterialOptionFlag __optionFlag = MaterialOptionFlag::NONE;
		static inline float __gamma = 1.f;

		constexpr void __setOption(const MaterialOptionFlag flags, const bool enabled) noexcept;

	protected:
		Material(const MaterialType materialType, const VertexAttributeType vertexType) noexcept;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept = 0;

		constexpr void useLighting(const bool enabled) noexcept;
		constexpr void useAmbientTexture(const bool enabled) noexcept;
		constexpr void useDiffuseTexture(const bool enabled) noexcept;
		constexpr void useSpecularTexture(const bool enabled) noexcept;
		constexpr void useEmissiveTexture(const bool enabled) noexcept;
		constexpr void useShininessTexture(const bool enabled) noexcept;
		constexpr void useAlphaTexture(const bool enabled) noexcept;
		constexpr void useNormalTexture(const bool enabled) noexcept;

	public:
		void render(ObjectGL::VertexArray &vertexArray, const GLsizei numInstances = 1) noexcept;

		static constexpr void setGamma(const float gamma) noexcept;

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

	constexpr void Material::useDiffuseTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::DIFFUSE_TEXTURE, enabled);
	}

	constexpr void Material::useSpecularTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SPECULAR_TEXTURE, enabled);
	}

	constexpr void Material::useEmissiveTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::EMISSIVE_TEXTURE, enabled);
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
}
