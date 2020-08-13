#include "PostProcessorPipeline.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	size_t PostProcessorPipeline::getNumProcessors() const noexcept
	{
		return __pipeline.size();
	}

	PostProcessor &PostProcessorPipeline::getProcessor(const size_t idx) noexcept
	{
		return *__pipeline[idx];
	}

	const PostProcessor &PostProcessorPipeline::getProcessor(const size_t idx) const noexcept
	{
		return *__pipeline[idx];
	}

	void PostProcessorPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		for (const unique_ptr<PostProcessor> &pProcessor : __pipeline)
			pProcessor->setScreenSize(width, height);
	}

	void PostProcessorPipeline::bind() noexcept
	{
		if (__pipeline.empty())
			return;

		__pipeline[0]->bind();
	}

	void PostProcessorPipeline::render() noexcept
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

		__pRenderTarget->bind();
		pPrevProcessor->render();
	}
}