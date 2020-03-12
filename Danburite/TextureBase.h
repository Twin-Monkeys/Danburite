#pragma once

#include "Object.h"
#include "TextureType.h"
#include "TextureException.h"
#include "UniformDeployable.h"
#include <cassert>

namespace ObjectGL
{
	class TextureBase abstract : public Object<GLuint>
	{
	private:
		GLuint64 __handle = 0ULL;

		TextureBase(const TextureBase &) = delete;
		TextureBase& operator=(const TextureBase &) = delete;

		void __release() noexcept;

		static GLuint __createTexObj();

	protected:
		const GLenum _RAW_TYPE;

		TextureBase(const TextureType type);
		void _bindID() noexcept;

	public:
		void bind(const GLuint location) noexcept;

		template <typename T>
		void setState(const TextureParamType paramType, const T value) noexcept;

		template <typename T>
		void setStates(const TextureParamType paramType, const T* const values) noexcept;

		template <typename T, size_t arrSize>
		void setStates(const TextureParamType paramType, const T(&values)[arrSize]) noexcept;

		GLuint64 getHandle(const bool resideIfCreated = true) noexcept;
		constexpr bool isHandleCreated() const noexcept;

		void reside() noexcept;
		void unreside() noexcept;

		virtual ~TextureBase() noexcept;

		static void unbind(const TextureType type, const GLint location) noexcept;
	};

	template <typename T>
	void TextureBase::setState(const TextureParamType paramType, const T value) noexcept
	{
		setStates(paramType, &value);
	}

	template <typename T>
	void TextureBase::setStates(const TextureParamType paramType, const T* const values) noexcept
	{
		using namespace std;
		constexpr bool IS_GL_TEX_PARAM_VALUE_TYPE =
			(
				is_same_v<T, GLfloat> ||
				is_same_v<T, GLint> ||
				is_same_v<T, GLuint> ||
				is_same_v<T, DepthStencilTextureModeValue> ||
				is_same_v<T, TextureCompareFuncValue> ||
				is_same_v<T, TextureCompareModeValue> ||
				is_same_v<T, TextureMinFilterValue> ||
				is_same_v<T, TextureMagFilterValue> ||
				is_same_v<T, TextureSwizzleValue> ||
				is_same_v<T, TextureWrapValue>
				);

		static_assert(
			IS_GL_TEX_PARAM_VALUE_TYPE,
			"The type parameter must be one of [GLfloat, GLint, GLuint] or its compatible types");

		assert(!__handle);
		_bindID();

		const GLenum GL_TEX_PARAM_TYPE = GLenum(paramType);

		if constexpr (is_same_v<T, GLfloat>)
			glTexParameterfv(_RAW_TYPE, GL_TEX_PARAM_TYPE, values);
		else
			glTexParameteriv(_RAW_TYPE, GL_TEX_PARAM_TYPE, reinterpret_cast<const GLint*>(values));
	}

	template <typename T, size_t arrSize>
	void TextureBase::setStates(const TextureParamType paramType, const T(&values)[arrSize]) noexcept
	{
		setStates(paramType, static_cast<const T *const>(values));
	}

	constexpr bool TextureBase::isHandleCreated() const noexcept
	{
		return __handle;
	}
}
