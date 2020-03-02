#pragma once

#include "PhongMaterial.h"
#include "OutliningMaterialComponent.h"

namespace Danburite
{
	class OutliningPhongMaterial : public Material, public PhongMaterialComponent, public OutliningMaterialComponent
	{
	protected:
		ObjectGL::Program &_phongProgram;
		ObjectGL::Program &_outlineProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		OutliningPhongMaterial(
			const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useSpecularTexture;
		using Material::useEmissiveTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~OutliningPhongMaterial() = default;
	};
}