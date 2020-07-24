#pragma once

#include "PostProcessor.h"

namespace Danburite
{
	class PostProcessingPipeline
	{
	private:
		AttachmentServer __attachmentServerPingPong[2];
		std::vector<std::unique_ptr<PostProcessor>> __pipeline;

	public:
		template <typename ProcessorType, typename ...Args>
		ProcessorType &appendProcessor(Args &&...args) noexcept;

		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void render() noexcept;

		virtual ~PostProcessingPipeline() = default;

		static void unbind() noexcept;
	};

	template <typename ProcessorType, typename ...Args>
	ProcessorType &PostProcessingPipeline::appendProcessor(Args &&...args) noexcept
	{
		using namespace std;

		static_assert(
			is_base_of_v<PostProcessor, ProcessorType>,
			"The type parameter must be derived of PostProcessor or its compatible types.");

		const size_t pingPongIdx = __pipeline.size();

		ProcessorType *const pRetVal = static_cast<ProcessorType *>(
			__pipeline.emplace_back(make_unique<ProcessorType>(forward<Args>(args)...)).get());

		pRetVal->setAttachmentServer(&__attachmentServerPingPong[pingPongIdx]);
		return *pRetVal;
	}
}
