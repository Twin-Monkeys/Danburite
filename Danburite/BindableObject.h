#pragma once

#include "Object.h"
#include <unordered_map>
#include <typeinfo>

namespace ObjectGL
{
	template <typename BindingType, typename IDType>
	class BindableObject : public Object<IDType>
	{
	private:
		size_t __bindingIndex = 0ULL;

		BindableObject(const BindableObject &) = delete;
		BindableObject &operator=(const BindableObject &) = delete;

		static size_t __getBindingIndex() noexcept;
		static IDType &__getBoundID(const size_t idx) noexcept;

	protected:
		constexpr BindableObject(const IDType &id) noexcept;
		virtual void _onBind() noexcept = 0;

		static void _unbind() noexcept;

	public:
		void bind() noexcept;
	};

	template <typename BindingType, typename IDType>
	constexpr BindableObject<BindingType, IDType>::BindableObject(const IDType &id) noexcept :
		Object<IDType>(id)
	{}

	template <typename BindingType, typename IDType>
	size_t BindableObject<BindingType, IDType>::__getBindingIndex() noexcept
	{
		return typeid(BindingType).hash_code();
	}

	template <typename BindingType, typename IDType>
	IDType &BindableObject<BindingType, IDType>::__getBoundID(const size_t idx) noexcept
	{
		static std::unordered_map<size_t, IDType> boundMap;
		return boundMap[idx];
	}

	template <typename BindingType, typename IDType>
	void BindableObject<BindingType, IDType>::bind() noexcept
	{
		if (!__bindingIndex)
			__bindingIndex = __getBindingIndex();

		IDType &curBound = __getBoundID(__bindingIndex);
		if (this->ID != curBound)
		{
			_onBind();
			curBound = this->ID;
		}
	}

	template <typename BindingType, typename IDType>
	void BindableObject<BindingType, IDType>::_unbind() noexcept
	{
		__getBoundID(__getBindingIndex()) = {};
	}
}