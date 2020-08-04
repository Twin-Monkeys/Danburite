#pragma once

#include <memory>
#include "MaterialType.h"
#include "MaterialOptionFlag.h"
#include "VertexArray.h"
#include "VertexAttributeFlag.h"
#include "Constant.h"
#include "UniformSetter.h"

namespace Danburite
{
	class Material abstract
	{
	private:
		const MaterialType __MATERIAL_TYPE;
		const VertexAttributeFlag __VERTEX_FLAG;
		MaterialOptionFlag __optionFlag = MaterialOptionFlag::NONE;

		ObjectGL::UniformSetter &__materialSetter;

		constexpr void __setOption(const MaterialOptionFlag flags, const bool enabled) noexcept;
		constexpr bool __isOptionEnabled(const MaterialOptionFlag flags) const noexcept;

	protected:
		Material(const MaterialType materialType, const VertexAttributeFlag vertexFlag) noexcept;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) = 0;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) = 0;

		constexpr void enableLighting(const bool enabled) noexcept;
		constexpr void enableAmbientTexture(const bool enabled) noexcept;
		constexpr void enableDiffuseTexture(const bool enabled) noexcept;
		constexpr void enableSpecularTexture(const bool enabled) noexcept;
		constexpr void enableEmissiveTexture(const bool enabled) noexcept;
		constexpr void enableShininessTexture(const bool enabled) noexcept;
		constexpr void enableAlphaTexture(const bool enabled) noexcept;
		constexpr void enableNormalTexture(const bool enabled) noexcept;
		constexpr void enableHeightTexture(const bool enabled) noexcept;

		constexpr bool isLightingEnabled() const noexcept;
		constexpr bool isAmbientTextureEnabled() const noexcept;
		constexpr bool isDiffuseTextureEnabled() const noexcept;
		constexpr bool isSpecularTextureEnabled() const noexcept;
		constexpr bool isEmissiveTextureEnabled() const noexcept;
		constexpr bool isShininessTextureEnabled() const noexcept;
		constexpr bool isAlphaTextureEnabled() const noexcept;
		constexpr bool isNormalTextureEnabled() const noexcept;
		constexpr bool isHeightTextureEnabled() const noexcept;

	public:
		constexpr void enableTranslucency(const bool enabled) noexcept;
		constexpr bool isTranslucencyEnabled() const noexcept;

		void render(ObjectGL::VertexArray &vertexArray, const GLsizei numInstances = 1) noexcept;
		void rawDrawcall(ObjectGL::VertexArray &vertexArray, const GLsizei numInstances = 1) noexcept;

		static void setGamma(const float gamma);

		virtual ~Material() = default;
	};

	constexpr void Material::__setOption(const MaterialOptionFlag flags, const bool enabled) noexcept
	{
		if (enabled)
			__optionFlag |= flags;
		else
			__optionFlag &= ~flags;
	}

	constexpr bool Material::__isOptionEnabled(const MaterialOptionFlag flags) const noexcept
	{
		return (__optionFlag & flags);
	}

	constexpr void Material::enableLighting(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::LIGHTING, enabled);
	}

	constexpr void Material::enableTranslucency(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::TRANSLUCENCY, enabled);
	}

	constexpr void Material::enableAmbientTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::AMBIENT_TEXTURE, enabled);
	}

	constexpr void Material::enableDiffuseTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::DIFFUSE_TEXTURE, enabled);
	}

	constexpr void Material::enableSpecularTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SPECULAR_TEXTURE, enabled);
	}

	constexpr void Material::enableEmissiveTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::EMISSIVE_TEXTURE, enabled);
	}

	constexpr void Material::enableShininessTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SHININESS_TEXTURE, enabled);
	}

	constexpr void Material::enableAlphaTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::ALPHA_TEXTURE, enabled);
	}

	constexpr void Material::enableNormalTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::NORMAL_TEXTURE, enabled);
	}

	constexpr void Material::enableHeightTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::HEIGHT_TEXTURE, enabled);
	}

	constexpr bool Material::isLightingEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::LIGHTING);
	}

	constexpr bool Material::isTranslucencyEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::TRANSLUCENCY);
	}

	constexpr bool Material::isAmbientTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::AMBIENT_TEXTURE);
	}

	constexpr bool Material::isDiffuseTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::DIFFUSE_TEXTURE);
	}

	constexpr bool Material::isSpecularTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::SPECULAR_TEXTURE);
	}

	constexpr bool Material::isEmissiveTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::EMISSIVE_TEXTURE);
	}

	constexpr bool Material::isShininessTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::SHININESS_TEXTURE);
	}

	constexpr bool Material::isAlphaTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::ALPHA_TEXTURE);
	}

	constexpr bool Material::isNormalTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::NORMAL_TEXTURE);
	}

	constexpr bool Material::isHeightTextureEnabled() const noexcept
	{
		return __isOptionEnabled(MaterialOptionFlag::HEIGHT_TEXTURE);
	}
}
