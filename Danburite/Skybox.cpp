#include "Skybox.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"
#include "VertexArrayFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Skybox::Skybox(const unordered_set<ProgramType> &programTypes) noexcept :
		__skyboxUniformSetter(programTypes)
	{
		using namespace ShaderIdentifier;
		static unordered_set<UniformSetter *> initializedSet;

		ProgramFactory &programFactory = ProgramFactory::getInstance();
		for (const ProgramType programType : programTypes)
		{
			UniformSetter *const pUniformSetter = &(programFactory.getProgram(programType));
			if (!initializedSet.emplace(pUniformSetter).second)
				continue;

			pUniformSetter->setUniformInt(Name::Cubemap::ALBEDO_TEX, Value::Cubemap::ALBEDO_TEX_LOCATION);
		}
	}

	void Skybox::draw() noexcept
	{
		_onDeploy(__skyboxUniformSetter);
		_onDraw(__skyboxUniformSetter);
	}

	void Skybox::_drawBoxVA() noexcept
	{
		VertexArray &cubeVA =
			VertexArrayFactory::getInstance().getVertexArrayReference(ShapeType::CUBE, VertexAttributeType::POS3);

		cubeVA.draw();
	}
}