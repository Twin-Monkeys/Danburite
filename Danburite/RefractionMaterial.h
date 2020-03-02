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
			ObjectGL::UniformSetter &uniformSetter, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		RefractionMaterial(const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		using Material::useNormalTexture;

		virtual ~RefractionMaterial() = default;
	};
}
