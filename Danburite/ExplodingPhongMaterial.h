#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class ExplodingPhongMaterial : public Material, public PhongMaterialComponent
	{
	protected:
		ObjectGL::Program &_explodingPhongProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ExplodingPhongMaterial(
			const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useSpecularTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~ExplodingPhongMaterial() = default;
	};
}
