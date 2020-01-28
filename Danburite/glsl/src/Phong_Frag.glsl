#version 460 core

#include "header/Phong_Header.glsl"

layout(early_fragment_tests) in;

in vec3 worldPos;
in vec4 color;
in vec3 worldNormal;
in vec2 texCoord;

out vec4 fragColor;

void main()
{
	// Normalizing normals in the vertex shader and then passing them to the fragment shader
	// doesn't ensure they are normalized after being passed.
	// By only passing the normals in the vertex shader and then
	// normalizing them in the fragment shader the problem (multisample white dot artifact) was fixed.
	fragColor = Phong_calcPhongColor(worldPos, normalize(worldNormal), texCoord, color);
} 