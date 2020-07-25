#pragma once

#include "Material.h"
#include "Program.h"
#include "RefractionMaterialComponent.h"

namespace Danburite
{
	class RefractionMaterial : public Material, public RefractionMaterialComponent
	{
	protected:
		ObjectGL::Program &_refractionProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		RefractionMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		using Material::useNormalTexture;

		virtual ~RefractionMaterial() = default;
	};
}
