#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VsOut
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
}
gsIn[];

out VsOut
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
}
gsOut;

uniform float displacementRatio = 1.f;

void passAttributes(const uint index)
{
	gsOut.worldPos = gsIn[index].worldPos;
	gsOut.color = gsIn[index].color;
	gsOut.worldNormal = gsIn[index].worldNormal;
	gsOut.texCoord = gsIn[index].texCoord;
}

vec3 getNormal()
{
	vec3 edge1 = (gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	vec3 edge2 = (gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);

	return normalize(cross(edge2, edge1));
}

vec4 calcDisplacement()
{
	return vec4(displacementRatio * getNormal(), 1.f);
}

void main()
{
	vec4 displacement = calcDisplacement();

	gl_Position = gl_in[0].gl_Position + displacement;
	passAttributes(0);
    EmitVertex();  
	
    gl_Position = gl_in[1].gl_Position + displacement;
	passAttributes(1);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + displacement;
	passAttributes(2);
    EmitVertex();

    EndPrimitive();
} 