#pragma once

#include "Material.h"
#include "SilhouetteMaterialComponent.h"

namespace Danburite
{
	class SilhouetteMaterial : public Material, public SilhouetteMaterialComponent
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter& target, ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		SilhouetteMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~SilhouetteMaterial() = default;
	};
}
