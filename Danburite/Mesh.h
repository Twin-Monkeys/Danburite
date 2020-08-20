#pragma once

#include "VertexArray.h"
#include "Material.h"
#include "ModelMatrixBuffer.h"
#include "BoneManager.h"

namespace Danburite
{
	class Mesh
	{
	private:
		const BoneManager &__boneMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		const std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial,
			const std::shared_ptr<ModelMatrixBuffer> &pModelMatrixBuffer,
			const BoneManager &boneManager) noexcept;

		[[nodiscard]]
		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;

		void draw(const GLsizei numInstances) noexcept;
		void rawDrawcall(const GLsizei numInstances) noexcept;

		template <typename $MaterialType, typename ...$Args>
		void drawUnderMaterialCondition(
			const size_t numInstances, bool($MaterialType::*const memberFunc)($Args ...args) const, $Args ...args) noexcept;

		virtual ~Mesh() = default;
	};

	constexpr const std::shared_ptr<Material> &Mesh::getMaterial() const noexcept
	{
		return __pMaterial;
	}

	template <typename $MaterialType, typename ...$Args>
	void Mesh::drawUnderMaterialCondition(
		const size_t numInstances, bool($MaterialType::*const memberFunc)($Args ...args) const, $Args ...args) noexcept
	{
		const Material &material = *__pMaterial;
		if ((material.*memberFunc)(std::forward<$Args>(args)...))
			draw(GLsizei(numInstances));
	}
}
