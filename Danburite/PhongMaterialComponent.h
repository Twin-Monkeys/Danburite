#pragma once

#include "Texture2D.h"
#include "Constant.h"
#include <memory>

namespace Danburite
{
	class PhongMaterialComponent : public ObjectGL::UniformDeployable
	{
	private:
		std::shared_ptr<ObjectGL::Texture2D> __pAmbientTex;
		std::shared_ptr<ObjectGL::Texture2D> __pDiffuseTex;
		std::shared_ptr<ObjectGL::Texture2D> __pSpecularTex;
		std::shared_ptr<ObjectGL::Texture2D> __pEmissiveTex;
		std::shared_ptr<ObjectGL::Texture2D> __pShininessTex;
		std::shared_ptr<ObjectGL::Texture2D> __pAlphaTex;
		std::shared_ptr<ObjectGL::Texture2D> __pNormalTex;

		float __shininess = Constant::Material::Phong::DEFAULT_SHININESS;

	protected:
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

	public:
		void setAmbientTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setDiffuseTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setSpecularTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setEmissiveTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		void setShininess(const float shininess) noexcept;
		void setShininessTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setAlphaTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;
		void setNormalTexture(const std::shared_ptr<ObjectGL::Texture2D> &pTexture) noexcept;

		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getAmbientTexture() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getDiffuseTexture() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getSpecularTexture() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getEmissiveTexture() const noexcept;

		constexpr float getShininess() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getShininessTexture() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getAlphaTexture() const noexcept;
		constexpr const std::shared_ptr<ObjectGL::Texture2D> &getNormalTexture() const noexcept;

		virtual ~PhongMaterialComponent() = default;
	};

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getAmbientTexture() const noexcept
	{
		return __pAmbientTex;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getDiffuseTexture() const noexcept
	{
		return __pDiffuseTex;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getSpecularTexture() const noexcept
	{
		return __pSpecularTex;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getEmissiveTexture() const noexcept
	{
		return __pEmissiveTex;
	}

	constexpr float PhongMaterialComponent::getShininess() const noexcept
	{
		return __shininess;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getShininessTexture() const noexcept
	{
		return __pShininessTex;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getAlphaTexture() const noexcept
	{
		return __pAlphaTex;
	}

	constexpr const std::shared_ptr<ObjectGL::Texture2D> &PhongMaterialComponent::getNormalTexture() const noexcept
	{
		return __pNormalTex;
	}
}
