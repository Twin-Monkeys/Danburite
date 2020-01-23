#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class TransparentPhongMaterial : public PhongMaterial
	{
	protected:
		virtual void _onRender(
			MaterialUniformSetter& target, ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		TransparentPhongMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~TransparentPhongMaterial() = default;
	};
}
