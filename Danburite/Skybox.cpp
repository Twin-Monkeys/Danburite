#include "Skybox.h"
#include "VertexArrayFactory.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Skybox::Skybox() :
		__skyboxProgram(ProgramFactory::getInstance().getProgram(ProgramType::SKYBOX)),
		__skyboxSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::SKYBOX)),
		__pCubeVA(VertexArrayFactory::createCube(VertexAttributeFlag::POS))
	{}

	void Skybox::setAlbedoTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pAlbedoTex = pTexture;
	}

	void Skybox::setLuminance(const float luminance) noexcept
	{
		__luminance = luminance;
	}

	void Skybox::draw() noexcept
	{
		if (!__enabled)
			return;

		__skyboxSetter.setUniformUvec2(
			ShaderIdentifier::Name::Skybox::ALBEDO_TEX, TextureUtil::getHandleIfExist(__pAlbedoTex));

		__skyboxSetter.setUniformFloat(ShaderIdentifier::Name::Skybox::LUMINANCE, __luminance);
		__skyboxProgram.bind();

		ContextStateManager &stateMgr = RenderContext::getCurrentStateManager();
		stateMgr.setDepthFunction(DepthStencilFunctionType::LEQUAL);
		stateMgr.setCulledFace(FacetType::FRONT);

		__pCubeVA->draw();
	}
}