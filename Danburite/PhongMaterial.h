#pragma once

#include "Material.h"
#include "Program.h"
#include "Texture2D.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class PhongMaterial : public Material
	{
	private:
		ObjectGL::Program &__phongProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::PHONG);

		std::shared_ptr<ObjectGL::Texture2D> __pAmbientTex;
		std::shared_ptr<ObjectGL::Texture2D> __pDiffuseTex;
		std::shared_ptr<ObjectGL::Texture2D> __pSpecularTex;
		std::shared_ptr<ObjectGL::Texture2D> __pEmissiveTex;
		std::shared_ptr<ObjectGL::Texture2D> __pShininessTex;
		std::shared_ptr<ObjectGL::Texture2D> __pAlphaTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;
		std::shared_ptr<ObjectGL::Texture2D> __pHeightTex;
		std::shared_ptr<ObjectGL::Texture2D> __pOcclusionTex;

		float __emissiveStrength = 1.f;
		float __shininess = Constant::Material::Phong::DEFAULT_SHININESS;

	protected:
		virtual void _onRender(
			DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

		virtual void _onRawDrawcall(
			DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		PhongMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		void setAmbientTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setDiffuseTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setSpecularTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		constexpr void setEmissiveStrength(const float strength) noexcept;
		void setEmissiveTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		constexpr void setShininess(const float shininess) noexcept;
		void setShininessTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setAlphaTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setHeightTexture(const std::shared_ptr<ObjectGL::Texture2D>& pTexture) noexcept;
		void setOcclusionTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		using Material::enableLighting;

		virtual ~PhongMaterial() = default;
	};

	constexpr void PhongMaterial::setEmissiveStrength(const float strength) noexcept
	{
		__emissiveStrength = strength;
	}

	constexpr void PhongMaterial::setShininess(const float shininess) noexcept
	{
		__shininess = shininess;
	}
}
