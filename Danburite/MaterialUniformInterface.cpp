#include "MaterialUniformInterface.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	MaterialUniformInterface::MaterialUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::MATERIAL,
			ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL
		},
		type				{ _appendField<GLuint, 4>(0) },
		optionFlag			{ _appendField<GLuint, 4>(0) },
		vertexFlag			{ _appendField<GLuint, 4>(0) },
		diffuseColor		{ _appendField<vec4, 16>(0.f, 0.f, 0.f) },
		gamma				{ _appendField<GLfloat, 4>(1.f) },
		emissiveStrength	{ _appendField<GLfloat, 4>(1.f) },
		shininess			{ _appendField<GLfloat, 4>(0.f) },
		ambientTex			{ _appendField<uvec2, 8>(0, 0) },
		diffuseTex			{ _appendField<uvec2, 8>(0, 0) },
		specularTex			{ _appendField<uvec2, 8>(0, 0) },
		emissiveTex			{ _appendField<uvec2, 8>(0, 0) },
		shininessTex		{ _appendField<uvec2, 8>(0, 0) },
		alphaTex			{ _appendField<uvec2, 8>(0, 0) },
		normalTex			{ _appendField<uvec2, 8>(0, 0) },
		heightTex			{ _appendField<uvec2, 8>(0, 0) },
		environmentTex		{ _appendField<uvec2, 8>(0, 0) },
		overriddenAlpha		{ _appendField<GLfloat, 4>(1.f) }
	{}
}