#pragma once

#include "Material.h"
#include "Program.h"
#include "PhongMaterialComponent.h"

namespace Danburite
{
	class PhongMaterial : public Material, public PhongMaterialComponent
	{
	protected:
		ObjectGL::Program &_phongProgram;

		PhongMaterial(const MaterialType materialType, const VertexAttributeFlag vertexFlag) noexcept;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		PhongMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useDiffuseTexture;
		using Material::useSpecularTexture;
		using Material::useEmissiveTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;
		using Material::useHeightTexture;

		virtual ~PhongMaterial() = default;
	};
}
