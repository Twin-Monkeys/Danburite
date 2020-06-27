#pragma once

#include "JointUpdateObserver.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class JointBase abstract
	{
	private:
		const std::string __name;

		glm::mat4 __targetJointMat { 1.f };

		ObjectGL::WeakPointerContainer<JointUpdateObserver> __observers;

	protected:
		virtual void _onUpdateMatrix(glm::mat4 &jointMat) noexcept = 0;

	public:
		JointBase(const std::string_view &name) noexcept;

		constexpr const std::string &getName() const noexcept;
		constexpr const glm::mat4 &getMatrix() const noexcept;

		constexpr ObjectGL::WeakPointerContainer<JointUpdateObserver> &getObserverSet() noexcept;
		constexpr const ObjectGL::WeakPointerContainer<JointUpdateObserver> &getObserverSet() const noexcept;

		JointBase &updateMatrix() noexcept;

		virtual ~JointBase() = default;
	};

	constexpr const std::string &JointBase::getName() const noexcept
	{
		return __name;
	}

	constexpr const glm::mat4 &JointBase::getMatrix() const noexcept
	{
		return __targetJointMat;
	}

	constexpr ObjectGL::WeakPointerContainer<JointUpdateObserver> &JointBase::getObserverSet() noexcept
	{
		return __observers;
	}

	constexpr const ObjectGL::WeakPointerContainer<JointUpdateObserver> &JointBase::getObserverSet() const noexcept
	{
		return __observers;
	}
}
