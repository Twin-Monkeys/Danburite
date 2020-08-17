#pragma once

#include "PostProcessor.h"
#include "BatchProcessor.h"
#include "SceneObject.h"
#include "Skybox.h"

namespace Danburite
{
	class PostProcessorPipeline
	{
	private:
		ObjectGL::FrameBuffer *__pRenderTarget = &ObjectGL::FrameBuffer::getDefault();

		AttachmentServer __attachmentServerPingPong[2];
		std::vector<std::unique_ptr<PostProcessor>> __pipeline;

	public:
		template <typename ProcessorType, typename ...Args>
		ProcessorType &appendProcessor(Args &&...args) noexcept;

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

	template <typename ProcessorType, typename ...Args>
	ProcessorType &PostProcessorPipeline::appendProcessor(Args &&...args) noexcept
	{
		using namespace std;

		static_assert(
			is_base_of_v<PostProcessor, ProcessorType>,
			"The type parameter must be derived of PostProcessor or its compatible types.");

		const size_t pingPongIdx = (__pipeline.size() % 2ULL);

		ProcessorType *const pRetVal = static_cast<ProcessorType *>(
			__pipeline.emplace_back(make_unique<ProcessorType>(forward<Args>(args)...)).get());

		pRetVal->setAttachmentServer(&__attachmentServerPingPong[pingPongIdx]);
		return *pRetVal;
	}

	constexpr void PostProcessorPipeline::setRenderTarget(ObjectGL::FrameBuffer &target) noexcept
	{
		__pRenderTarget = &target;
	}
}
