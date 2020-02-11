#include "PostProcessingPipeline.h"

using namespace std;

namespace Danburite
{
	void PostProcessingPipeline::appendProcessor(const weak_ptr<PostProcessor> &pProcessor) noexcept
	{
		__pipeline.emplace_back(pProcessor);
	}

	void PostProcessingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		for (auto it = __pipeline.begin(); it != __pipeline.end();)
		{
			const shared_ptr<PostProcessor> &pShared = it->lock();
			if (!pShared)
			{
				it = __pipeline.erase(it);
				continue;
			}

			pShared->setScreenSize(width, height);
			it++;
		}
	}

	void PostProcessingPipeline::bind() noexcept
	{
		if (__pipeline.empty())
			return;

		const shared_ptr<PostProcessor> &pFirst = __pipeline[0].lock();
		if (!pFirst)
		{
			__pipeline.erase(__pipeline.begin());
			bind();
		}
		else
			pFirst->bind();
	}

	void PostProcessingPipeline::render() noexcept
	{
		if (__pipeline.empty())
			return;

		if (__pipeline[0].expired())
		{
			__pipeline.erase(__pipeline.begin());
			return;
		}

		shared_ptr<PostProcessor> pPrevProcessor = __pipeline[0].lock();
		for (auto it = (__pipeline.begin() + 1); it != __pipeline.end();)
		{
			const shared_ptr<PostProcessor> &pCurProcessor = it->lock();
			if (!pCurProcessor)
			{
				it = __pipeline.erase(it);
				continue;
			}

			pCurProcessor->bind();
			pPrevProcessor->render();
			pPrevProcessor = pCurProcessor;

			it++;
		}

		PostProcessor::unbind();
		pPrevProcessor->render();
	}

	void PostProcessingPipeline::unbind() noexcept
	{
		PostProcessor::unbind();
	}
}