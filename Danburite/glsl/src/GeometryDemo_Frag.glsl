#version 460 core
layout(early_fragment_tests) in;

in GS_OUT
{
	vec3 color;
}
fs_in;

out vec4 fragColor;

void main()
{
	fragColor = vec4(fs_in.color, 1.f);
} 