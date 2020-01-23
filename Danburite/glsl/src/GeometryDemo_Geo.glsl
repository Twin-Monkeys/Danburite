#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

/*
	Because the geometry shader acts on a set of vertices as its input,
	its input data from the vertex shader is always represented as
	arrays of data even though we only have a single vertex right now.
*/
in VS_OUT
{
	vec3 color;
}
gs_in[];

out GS_OUT
{
	vec3 color;
}
gs_out;

void main()
{
	gs_out.color = gs_in[0].color;
	gl_Position = gl_in[0].gl_Position + vec4(-1.f, -1.f, 0.f, 0.f);    // 1:bottom-left
    EmitVertex();   
    gl_Position = gl_in[0].gl_Position + vec4(1.f, -1.f, 0.f, 0.f);    // 2:bottom-right
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-1.f, 1.f, 0.f, 0.f);    // 3:top-left
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(1.f, 1.f, 0.f, 0.f);    // 4:top-right
    EmitVertex();

	gs_out.color = vec3(1.f, 1.f, 1.f);
    gl_Position = gl_in[0].gl_Position + vec4(0.f, 2.f, 0.f, 0.f);    // 5:top
    EmitVertex();

    EndPrimitive();
} 