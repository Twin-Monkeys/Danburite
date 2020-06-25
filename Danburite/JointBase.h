#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Danburite
{
	class JointBase abstract
	{
	private:
		const std::string __name;

		glm::mat4 __jointMat { 1.f };

	protected:
		virtual void _onUpdateMatrix(glm::mat4 &jointMat) noexcept = 0;

	public:
		JointBase(const std::string_view &name) noexcept;

		constexpr const std::string &getName() const noexcept;
		constexpr const glm::mat4 &getMatrix() const noexcept;

		JointBase &updateMatrix() noexcept;

		virtual ~JointBase() = default;
	};

	constexpr const std::string &JointBase::getName() const noexcept
	{
		return __name;
	}

	constexpr const glm::mat4 &JointBase::getMatrix() const noexcept
	{
		return __jointMat;
	}
}
