#pragma once

#include "Material.h"
#include "MonoColorMaterialComponent.h"

namespace Danburite
{
	class MonoColorMaterial : public Material, public MonoColorMaterialComponent
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		MonoColorMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~MonoColorMaterial() = default;
	};
}