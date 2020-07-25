#pragma once

#include "Material.h"
#include "ReflectionMaterialComponent.h"
#include "Program.h"

namespace Danburite
{
	class ReflectionMaterial : public Material, public ReflectionMaterialComponent
	{
	protected:
		ObjectGL::Program &_reflectionProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ReflectionMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		using Material::useNormalTexture;

		virtual ~ReflectionMaterial() = default;
	};
}
