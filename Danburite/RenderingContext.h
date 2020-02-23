#pragma once

#include "BindableObject.h"
#include "PixelFormatDescriptor.h"
#include "RCAttributeDescriptor.h"
#include "RCException.h"

namespace ObjectGL
{
	class DeviceContext;

	class RenderingContext final : public BindableObject<RenderingContext, HGLRC>
	{
	private:
		DeviceContext &__deviceContext;

		RenderingContext(const RenderingContext &src) = delete;
		RenderingContext& operator=(const RenderingContext &) = delete;

		void __release() noexcept;

		static inline bool __glInitialized = false;
		static inline RenderingContext *__pCurrent = nullptr;

		static HGLRC __createRC(
			DeviceContext &deviceContext,
			const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc);

		static void __validate(DeviceContext &deviceContext);
		static void __setPixelFormat(const HDC hDC, const PIXELFORMATDESCRIPTOR &descRaw);

	protected:
		virtual void _onBind() noexcept override;

	public:
		RenderingContext(
			DeviceContext &deviceContext,
			const PixelFormatDescriptor& pixelFormatDesc, const RCAttributeDescriptor &attributeDesc);

		virtual ~RenderingContext() noexcept;

		static void requestBufferSwapping() noexcept;
		static void requestScreenClose() noexcept;
		static void unbind() noexcept;
	};
}