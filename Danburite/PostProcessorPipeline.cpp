#include "PostProcessorPipeline.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	FrameBuffer &PostProcessorPipeline::getFrameBuffer() noexcept
	{
		if (__pipeline.empty())
			return *__pRenderTarget;

		return __pipeline[0]->getFrameBuffer();
	}

	const FrameBuffer &PostProcessorPipeline::getFrameBuffer() const noexcept
	{
		if (__pipeline.empty())
			return *__pRenderTarget;

		return __pipeline[0]->getFrameBuffer();
	}

	void PostProcessorPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		for (const unique_ptr<PostProcessor> &pProcessor : __pipeline)
			pProcessor->setScreenSize(width, height);
	}

	void PostProcessorPipeline::render(
		const SetupTransaction &sceneDrawingSetup,
		BatchProcessor<SceneObject> &drawer, Skybox &skybox, const FrameBufferBlitFlag bufferClearFlag) noexcept
	{
		PostProcessor* pCurProcessor = nullptr;
		PostProcessor* pNextProcessor = nullptr;

		if (__pipeline.empty())
			__pRenderTarget->clearBuffers(bufferClearFlag);
		else
		{
			pCurProcessor = __pipeline[0].get();
			pCurProcessor->getFrameBuffer().clearBuffers(bufferClearFlag);
		}

		sceneDrawingSetup.setup();
		drawer.process(&SceneObject::draw);
		/*drawer.process([](SceneObject& iter)
		{
			iter.drawUnderMaterialCondition(false, &Material::isTranslucencyEnabled);
		});*/

		skybox.draw();

		for (size_t i = 1ULL; i < __pipeline.size(); i++)
		{
			pNextProcessor = __pipeline[i].get();

			pCurProcessor->render(pNextProcessor->getFrameBuffer());
			pCurProcessor = pNextProcessor;
		}

		if (pCurProcessor)
			pCurProcessor->render(*__pRenderTarget);
	}
}