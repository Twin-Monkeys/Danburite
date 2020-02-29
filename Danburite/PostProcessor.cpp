#include "PostProcessor.h"
#include "VertexArrayFactory.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PostProcessor::PostProcessor(const ProgramType type) :
		__pFrameBuffer(make_unique<FrameBuffer>()),
		__pVertexArray(VertexArrayFactory::getInstance().getVertexArrayPtr(ShapeType::RECTANGLE, VertexAttributeType::POS3_TEXCOORD2)),
		__pProgram(&(ProgramFactory::getInstance().getProgram(type)))
	{
		using namespace ShaderIdentifier;

		static unordered_set<UniformSetter *> initializedSet;
		if (!initializedSet.emplace(__pProgram).second)
			return;

		__pProgram->setUniformInt(Name::PostProcess::DEPTH_ATTACHMENT, Value::PostProcess::DEPTH_ATTACHMENT_LOCATION);
		__pProgram->setUniformInt(Name::PostProcess::STENCIL_ATTACHMENT, Value::PostProcess::STENCIL_ATTACHMENT_LOCATION);

		for (GLuint i = 0; i < Value::PostProcess::MAX_NUM_COLOR_ATTACHMENTS; i++)
		{
			const string &colorAttachmentName =
				(Name::PostProcess::COLOR_ATTACHMENT_ARRAY + ('[' + to_string(i) + ']'));

			__pProgram->setUniformInt(
				colorAttachmentName, Value::PostProcess::COLOR_ATTACHMENT_ARRAY_LOCATION + i);
		}
	}

	void PostProcessor::_attach(const AttachmentType attachmentType, Attachable &attachment) noexcept
	{
		__pFrameBuffer->attach(attachmentType, attachment);
	}

	bool PostProcessor::_detach(const AttachmentType attachmentType) noexcept
	{
		return __pFrameBuffer->detach(attachmentType);
	}

	void PostProcessor::bind() noexcept
	{
		__pFrameBuffer->bind();
	}

	void PostProcessor::render() noexcept
	{
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, false);

		_onRender();
		__pProgram->bind();
		__pVertexArray->draw();

		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	}

	void PostProcessor::unbind() noexcept
	{
		FrameBuffer::unbind();
	}
}