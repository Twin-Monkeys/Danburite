#pragma once

#include "Material.h"
#include "PhongMaterialComponent.h"

namespace Danburite
{
	class PhongMaterial : public Material, public PhongMaterialComponent
	{
	protected:
		PhongMaterial(
			const std::unordered_set<ProgramType> &programTypes,
			const MaterialType type, const VertexAttributeType vertexType) noexcept;

		virtual void _onDeploy(MaterialUniformSetter &materialSetterr) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		PhongMaterial(const VertexAttributeType vertexType) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useSpecularTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~PhongMaterial() = default;
	};
}
