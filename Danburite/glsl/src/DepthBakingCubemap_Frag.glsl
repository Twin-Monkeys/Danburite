#version 460 core

#include "header/DepthBakingCubemap_Header.glsl"

in vec3 worldPos;

void main()
{
    gl_FragDepth = DepthBakingCubemap_getDepth(worldPos);
}