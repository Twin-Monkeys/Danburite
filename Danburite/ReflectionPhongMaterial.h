#pragma once

#include "PhongMaterial.h"
#include "TextureCubemap.h"

namespace Danburite
{
	class ReflectionPhongMaterial : public Material, public PhongMaterialComponent
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;

	protected:
		ObjectGL::Program &_reflectionPhongProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ReflectionPhongMaterial(const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;

		using Material::useLighting;
		using Material::useAmbientTexture;
		using Material::useSpecularTexture;
		using Material::useShininessTexture;
		using Material::useAlphaTexture;
		using Material::useNormalTexture;

		virtual ~ReflectionPhongMaterial() = default;
	};
}