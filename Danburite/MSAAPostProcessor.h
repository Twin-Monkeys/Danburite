#pragma once

#include "PostProcessor.h"
#include "Program.h"
#include "TextureMultisample.h"
#include "RenderBufferMultisample.h"
#include "ShaderIdentifier.h"
#include "SetupTransaction.h"
#include "FullscreenDrawer.h"

namespace Danburite
{
	class MSAAPostProcessor : public PostProcessor
	{
	private:
		const GLsizei __NUM_SAMPLE_POINTS;
		const bool __FIXED_SAMPLE_LOCATIONS;
		const bool __attachDepthBuffer;

		ObjectGL::Program &__program;
		std::shared_ptr<ObjectGL::TextureMultisample> __pColorAttachment;
		std::shared_ptr<ObjectGL::RenderBufferMultisample> __pDepthStencilAttachment;

		ObjectGL::UniformBuffer &__texContainerSetter;
		FullscreenDrawer &__fullscreenDrawer;

		SetupTransaction __setupTransaction;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		MSAAPostProcessor(
			const bool attachDepthBuffer = false,
			const GLsizei numSamplePoints = ShaderIdentifier::Value::MSAA::NUM_SAMPLE_POINTS,
			const bool fixedSampleLocations = true);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~MSAAPostProcessor() = default;
	};
}