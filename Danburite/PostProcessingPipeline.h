#pragma once

#include "PostProcessor.h"

namespace Danburite
{
	class PostProcessingPipeline
	{
	private:
		std::vector<PostProcessor *> __pipeline;

	public:
		void addProcessor(PostProcessor *const pProcessor) noexcept;
		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void render() noexcept;

		virtual ~PostProcessingPipeline() = default;

		static void unbind() noexcept;
	};
}
