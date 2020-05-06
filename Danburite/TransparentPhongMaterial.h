#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class TransparentPhongMaterial : public PhongMaterial
	{
	protected:
		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		TransparentPhongMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		virtual ~TransparentPhongMaterial() = default;
	};
}
