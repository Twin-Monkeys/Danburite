#pragma once

#include "JointUpdateObserver.h"
#include "Transform.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class SceneNodeConnecterBase abstract
	{
	private:
		const std::string __nodeName;

		glm::mat4 __connectingMat { 1.f };

	protected:
		virtual void _onUpdateLocalMatrix(glm::mat4 &localConnectingMat) noexcept = 0;

	public:
		SceneNodeConnecterBase(const std::string_view &nodeName) noexcept;

		constexpr const std::string &getNodeName() const noexcept;
		constexpr const glm::mat4 &getMatrix() const noexcept;

		SceneNodeConnecterBase &updateMatrix() noexcept;

		virtual ~SceneNodeConnecterBase() = default;
	};

	constexpr const std::string &SceneNodeConnecterBase::getNodeName() const noexcept
	{
		return __nodeName;
	}

	constexpr const glm::mat4 &SceneNodeConnecterBase::getMatrix() const noexcept
	{
		return __connectingMat;
	}
}
