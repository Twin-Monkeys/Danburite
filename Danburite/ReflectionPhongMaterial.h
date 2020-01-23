#pragma once

#include "PhongMaterial.h"
#include "TextureCubemap.h"

namespace Danburite
{
	class ReflectionPhongMaterial : public PhongMaterial
	{
	private:
		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetterr) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ReflectionPhongMaterial(const VertexAttributeType vertexType) noexcept;

		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;

		virtual ~ReflectionPhongMaterial() = default;
	};
}