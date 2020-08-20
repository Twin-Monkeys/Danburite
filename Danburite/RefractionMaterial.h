#pragma once

#include "Material.h"
#include "Program.h"
#include "TextureCubemap.h"
#include "Texture2D.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

namespace Danburite
{
	class RefractionMaterial : public Material
	{
	private:
		ObjectGL::Program &__refractionProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::REFRACTION);

		std::shared_ptr<ObjectGL::TextureCubemap> __pEnvTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

	protected:
		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			ObjectGL::UniformSetter& materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		RefractionMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		void setEnvironmentTexture(const std::shared_ptr<ObjectGL::TextureCubemap> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		virtual ~RefractionMaterial() = default;
	};
}
