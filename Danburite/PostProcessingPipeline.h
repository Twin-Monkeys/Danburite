#pragma once

#include "PostProcessor.h"

namespace Danburite
{
	class PostProcessingPipeline
	{
	private:
		std::vector<std::weak_ptr<PostProcessor>> __pipeline;

	public:
		void appendProcessor(const std::weak_ptr<PostProcessor> &pProcessor) noexcept;
		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void render() noexcept;

		virtual ~PostProcessingPipeline() = default;

		static void unbind() noexcept;
	};
}
