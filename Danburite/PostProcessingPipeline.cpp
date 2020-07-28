#include "PostProcessingPipeline.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	size_t PostProcessingPipeline::getNumProcessors() const noexcept
	{
		return __pipeline.size();
	}

	PostProcessor &PostProcessingPipeline::getProcessor(const size_t idx) noexcept
	{
		return *__pipeline[idx];
	}

	const PostProcessor &PostProcessingPipeline::getProcessor(const size_t idx) const noexcept
	{
		return *__pipeline[idx];
	}

	void PostProcessingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		for (const unique_ptr<PostProcessor> &pProcessor : __pipeline)
			pProcessor->setScreenSize(width, height);
	}

	void PostProcessingPipeline::bind() noexcept
	{
		if (__pipeline.empty())
			return;

		__pipeline[0]->bind();
	}

	void PostProcessingPipeline::render() noexcept
	{
		if (__pipeline.empty())
			return;

		PostProcessor *pPrevProcessor = __pipeline[0].get();
		for (size_t i = 1ULL; i < __pipeline.size(); i++)
		{
			PostProcessor *const pCurProcessor = __pipeline[i].get();

			pCurProcessor->bind();
			pPrevProcessor->render(pCurProcessor);
			pPrevProcessor = pCurProcessor;
		}

		PostProcessor::unbind();
		pPrevProcessor->render();
	}

	void PostProcessingPipeline::unbind() noexcept
	{
		PostProcessor::unbind();
	}
}