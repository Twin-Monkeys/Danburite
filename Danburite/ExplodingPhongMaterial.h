#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class ExplodingPhongMaterial : public Material, public PhongMaterialComponent
	{
	protected:
		ObjectGL::Program &_explodingPhongProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ExplodingPhongMaterial(const VertexAttributeType vertexType) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useDiffuseTexture;
		using Material::useSpecularTexture;
		using Material::useEmissiveTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~ExplodingPhongMaterial() = default;
	};
}
