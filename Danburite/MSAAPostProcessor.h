#pragma once

#include "PostProcessor.h"
#include "TextureMultisample.h"
#include "RenderBufferMultisample.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class MSAAPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::Program &__program;

		const GLsizei NUM_SAMPLE_POINTS;
		const bool FIXED_SAMPLE_LOCATIONS;

		std::unique_ptr<ObjectGL::TextureMultisample> __pColorAttachment;
		std::unique_ptr<ObjectGL::RenderBufferMultisample> __pDepthStencilAttachment;

	protected:
		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		MSAAPostProcessor(
			const GLsizei numSamplePoints = ShaderIdentifier::Value::MSAA::NUM_SAMPLE_POINTS,
			const bool fixedSampleLocations = true);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~MSAAPostProcessor() = default;
	};
}