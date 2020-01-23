#pragma once

#include "PhongMaterial.h"
#include "OutliningMaterialComponent.h"

namespace Danburite
{
	class OutliningPhongMaterial : public PhongMaterial, public OutliningMaterialComponent
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetterr) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		OutliningPhongMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~OutliningPhongMaterial() = default;
	};
}