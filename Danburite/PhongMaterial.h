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

		PhongMaterial(
			const MaterialType materialType,
			const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		PhongMaterial(const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useSpecularTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~PhongMaterial() = default;
	};
}
