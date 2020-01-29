#pragma once

#include "MaterialUniformDeployable.h"
#include "Texture2D.h"

namespace Danburite
{
	class PhongMaterialComponent : virtual public MaterialUniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::Texture2D> __pAmbientTex;
		std::shared_ptr<ObjectGL::Texture2D> __pDiffuseTex;
		std::shared_ptr<ObjectGL::Texture2D> __pSpecularTex;
		std::shared_ptr<ObjectGL::Texture2D> __pEmissiveTex;
		std::shared_ptr<ObjectGL::Texture2D> __pShininessTex;
		std::shared_ptr<ObjectGL::Texture2D> __pAlphaTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

		float __shininess = 20.f;

	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetter) noexcept override;

	public:
		void setAmbientTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setDiffuseTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setSpecularTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setEmissiveTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		void setShininess(const float shininess) noexcept;
		void setShininessTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setAlphaTexture(const std::shared_ptr<ObjectGL::Texture2D>& pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		const std::shared_ptr<ObjectGL::Texture2D> &getAmbientTexture() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getDiffuseTexture() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getSpecularTexture() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getEmissiveTexture() const noexcept;

		float getShininess() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getShininessTexture() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getAlphaTexture() const noexcept;
		const std::shared_ptr<ObjectGL::Texture2D> &getNormalTexture() const noexcept;

		virtual ~PhongMaterialComponent() = default;
	};
}
