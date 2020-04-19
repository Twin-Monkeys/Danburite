#version 460 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

#define VariableInOut_Geo_exportToFrag_worldPos
#include "header/VariableInOut_Geo_Header.glsl"
#include "header/DepthBakingCubemap_Header.glsl"

void main()
{
    // gl_Layer: built-in variable that specifies to which face we render.
	for(gl_Layer = 0; gl_Layer < 6; gl_Layer++)
    {
        for(int i = 0; i < 3; i++)
        {
            variableInOut_GeoToFrag.worldPos = gl_in[i].gl_Position.xyz;
            gl_Position = DepthBakingCubemap_getNDCPosition(gl_Layer, variableInOut_GeoToFrag.worldPos);
            EmitVertex();
        }    
        EndPrimitive();
    }
}