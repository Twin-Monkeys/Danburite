#version 460 core

#include "header/Phong_Header.glsl"

in VariableInOut_Vert
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
	mat3 TBN;
}
variableInOut_Vert;

out vec4 fragColor;

void main()
{
	// Normalizing normals in the vertex shader and then passing them to the fragment shader
	// doesn't ensure they are normalized after being passed.
	// By only passing the normals in the vertex shader and then
	// normalizing them in the fragment shader the problem (multisample white dot artifact) was fixed.
	fragColor = Phong_calcPhongColor(variableInOut_Vert.worldPos, normalize(variableInOut_Vert.worldNormal), variableInOut_Vert.TBN, variableInOut_Vert.texCoord, variableInOut_Vert.color);
} 