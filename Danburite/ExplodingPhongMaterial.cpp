#include "ExplodingPhongMaterial.h"
#include "ShaderIdentifier.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ExplodingPhongMaterial::ExplodingPhongMaterial(const VertexAttributeType vertexType) noexcept :
		PhongMaterial({ ProgramType::EXPLODING_PHONG }, MaterialType::EXPLODING_PHONG, vertexType)
	{}

	void ExplodingPhongMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::EXPLODING_PHONG).bind();
		vertexArray.draw(numInstances);
	}
}