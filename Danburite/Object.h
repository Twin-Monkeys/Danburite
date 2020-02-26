#pragma once

#include <gl/glew.h>

namespace ObjectGL
{
	template <typename IDType>
	class Object
	{
	private:
		Object(const Object &) = delete;
		Object &operator=(const Object &) = delete;

	protected:
		constexpr Object(const IDType &id) noexcept;

	public:
		const IDType ID;

		virtual ~Object() = default;
	};

	template <typename IDType>
	constexpr Object<IDType>::Object(const IDType &id) noexcept :
		ID(id)
	{}
}
