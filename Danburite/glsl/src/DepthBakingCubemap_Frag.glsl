#version 460 core

#define VariableInOut_Frag_importFromGeo_worldPos
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/DepthBakingCubemap_Header.glsl"

void main()
{
    gl_FragDepth = DepthBakingCubemap_getDepth(variableInOut_GeoToFrag.worldPos);
}