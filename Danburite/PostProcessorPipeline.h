#pragma once

#include "PostProcessor.h"
#include "BatchProcessor.h"
#include "SceneObject.h"
#include "Skybox.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class PostProcessorPipeline
	{
	private:
		AttachmentServer __attachmentServerPingPong[2];

		ObjectGL::FrameBuffer *__pRenderTarget = &ObjectGL::FrameBuffer::getDefault();

		std::unique_ptr<ObjectGL::FrameBuffer>
			__pWboitAccumFB = std::make_unique<ObjectGL::FrameBuffer>();

		std::shared_ptr<ObjectGL::RenderBuffer> __pWboitDepthStencilAttachment;

		std::vector<std::unique_ptr<PostProcessor>> __pipeline;

		ObjectGL::UniformBuffer &__translucencySwitcherSetter = 
			UniformBufferFactory::getInstance().getUniformBuffer(
				ShaderIdentifier::Name::UniformBuffer::TRANSLUCENCY_SWITCHER);

	public:
		template <typename ProcessorType, typename ...$Args>
		ProcessorType &appendProcessor($Args &&...args) noexcept;

		ObjectGL::FrameBuffer& getFrameBuffer() noexcept;
		const ObjectGL::FrameBuffer& getFrameBuffer() const noexcept;

		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;
		void render(
			const SetupTransaction &sceneDrawingSetup,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox,
			const ObjectGL::FrameBufferBlitFlag bufferClearFlag) noexcept;

		constexpr void setRenderTarget(ObjectGL::FrameBuffer &target) noexcept;

		virtual ~PostProcessorPipeline() = default;
	};

	template <typename ProcessorType, typename ...$Args>
	ProcessorType &PostProcessorPipeline::appendProcessor($Args &&...args) noexcept
	{
		using namespace std;

		static_assert(
			is_base_of_v<PostProcessor, ProcessorType>,
			"The type parameter must be derived of PostProcessor or its compatible types.");

		const size_t pingPongIdx = (__pipeline.size() % 2ULL);

		ProcessorType *const pRetVal = static_cast<ProcessorType *>(
			__pipeline.emplace_back(make_unique<ProcessorType>(forward<$Args>(args)...)).get());

		pRetVal->setAttachmentServer(&__attachmentServerPingPong[pingPongIdx]);
		return *pRetVal;
	}

	constexpr void PostProcessorPipeline::setRenderTarget(ObjectGL::FrameBuffer &target) noexcept
	{
		__pRenderTarget = &target;
	}
}
