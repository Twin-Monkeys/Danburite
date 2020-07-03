#pragma once

#include "ModelMatrixBuffer.h"
#include "AnimationManager.h"
#include "SceneObjectNode.h"
#include "Drawable.h"

namespace Danburite
{
	class SceneObject : public Updatable, public Drawable, public JointUpdateObserver
	{
	private:
		const std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer = std::make_shared<ModelMatrixBuffer>();
		AnimationManager __animMgr;

		std::vector<std::unique_ptr<BoneManager>> __boneMgrs;
		std::vector<std::unique_ptr<SceneObjectNode>> __nodes;
		std::vector<std::unique_ptr<Joint>> __joints;

		SceneObjectNode *__pRootNode = nullptr;

	public:
		SceneObjectNode &createNode(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial,
			BoneManager &boneManager,
			const bool setAsRoot = false,
			const std::string_view &name = "NO_NAMED") noexcept;

		SceneObjectNode &createNode(
			const std::vector<std::tuple<
				std::shared_ptr<ObjectGL::VertexArray>, std::shared_ptr<Material>, BoneManager *>> &meshDataList,
			const bool setAsRoot = false,
			const std::string_view &name = "NO_NAMED") noexcept;
		
		BoneManager &createBoneManager() noexcept;

		size_t getNumInstances() const noexcept;
		void setNumInstances(const GLsizei numInstances) noexcept;

		Transform &getTransform(const size_t idx = 0) noexcept;
		const Transform &getTransform(const size_t idx = 0) const noexcept;

		constexpr SceneObjectNode *getRootNode() noexcept;
		constexpr const SceneObjectNode *getRootNode() const noexcept;

		constexpr SceneObject &setRootNode(SceneObjectNode &node) noexcept;

		SceneObjectNode *getNode(const std::string_view &name) noexcept;
		const SceneObjectNode *getNode(const std::string_view &name) const noexcept;

		AnimationManager &getAnimationManager() noexcept;
		const AnimationManager &getAnimationManager() const noexcept;

		virtual void update(const float deltaTime) noexcept override;

		virtual void draw() noexcept override;
		virtual void rawDrawcall() noexcept override;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual void onUpdateJointMatrix(
			const std::string &nodeName, const glm::mat4 &jointMatrix) noexcept override;
	};

	constexpr SceneObjectNode *SceneObject::getRootNode() noexcept
	{
		return __pRootNode;
	}

	constexpr const SceneObjectNode *SceneObject::getRootNode() const noexcept
	{
		return __pRootNode;
	}

	constexpr SceneObject &SceneObject::setRootNode(SceneObjectNode &node) noexcept
	{
		__pRootNode = &node;
		return *this;
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void SceneObject::traverseMaterial(const FunctionType function, Args &&...args)
	{
		__pRootNode->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}