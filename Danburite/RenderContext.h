#pragma once

#include "BindableObject.h"
#include "PixelFormatDescriptor.h"
#include "RCAttributeDescriptor.h"
#include "RCException.h"
#include <unordered_set>
#include <cassert>

namespace ObjectGL
{
	class DeviceContext;
	class RenderContext;

	template <typename T>
	class ContextDependentSingleton abstract
	{
		friend RenderContext;

	private:
		static std::unordered_map<
			const RenderContext *, std::unique_ptr<T>> &__getInstanceMap() noexcept;

		static void __contextInit(const RenderContext *const pRenderContext) noexcept;
		static void __contextDestroy(const RenderContext *const pRenderContext) noexcept;

	public:
		static T &getInstance() noexcept;
	};

	class RenderContext final : public BindableObject<RenderContext, HGLRC>
	{
	private:
		DeviceContext &__deviceContext;

		static inline
			std::unordered_set<void(*)(const RenderContext *)>
			__onCreateListeners, __onDestroyListeners;

		RenderContext(const RenderContext &src) = delete;
		RenderContext& operator=(const RenderContext &) = delete;

		void __release() noexcept;

		static inline bool __glInitialized = false;
		static inline RenderContext *__pCurrent = nullptr;

		static HGLRC __createRC(
			DeviceContext &deviceContext,
			const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc);

		static void __validate(DeviceContext &deviceContext);
		static void __setPixelFormat(const HDC hDC, const PIXELFORMATDESCRIPTOR &descRaw);

	protected:
		virtual void _onBind() noexcept override;

	public:
		RenderContext(
			DeviceContext &deviceContext,
			const PixelFormatDescriptor& pixelFormatDesc, const RCAttributeDescriptor &attributeDesc);

		virtual ~RenderContext() noexcept;

		static void requestBufferSwapping() noexcept;
		static void requestScreenClose() noexcept;
		static void unbind() noexcept;

		static constexpr RenderContext *getCurrent() noexcept;

		template <typename T>
		static void registerContextDependentSingleton() noexcept;
	};

	template <typename T>
	std::unordered_map<
		const RenderContext *, std::unique_ptr<T>> &ContextDependentSingleton<T>::__getInstanceMap() noexcept
	{
		static std::unordered_map<const RenderContext *, std::unique_ptr<T>> instanceMap;
		return instanceMap;
	}

	template <typename T>
	void ContextDependentSingleton<T>::__contextInit(const RenderContext* const pRenderContext) noexcept
	{
		auto &instanceMap = __getInstanceMap();
		auto result = instanceMap.emplace(pRenderContext, new T {});

		assert(result.second);
	}

	template <typename T>
	void ContextDependentSingleton<T>::__contextDestroy(const RenderContext* const pRenderContext) noexcept
	{
		auto &instanceMap = __getInstanceMap();
		const size_t result = instanceMap.erase(pRenderContext);

		assert(result);
	}

	template <typename T>
	T &ContextDependentSingleton<T>::getInstance() noexcept
	{
		return *(__getInstanceMap().at(RenderContext::getCurrent()));
	}

	constexpr RenderContext *RenderContext::getCurrent() noexcept
	{
		return __pCurrent;
	}

	template <typename T>
	void RenderContext::registerContextDependentSingleton() noexcept
	{
		__onCreateListeners.emplace(ContextDependentSingleton<T>::__contextInit);
		__onDestroyListeners.emplace(ContextDependentSingleton<T>::__contextDestroy);
	}
}