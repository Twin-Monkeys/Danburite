//? #version 460 core

#include "Constant_Header.glsl"

layout(location = POSITION_LOCATION) in vec3 VertexAttribute_pos;
layout(location = COLOR_LOCATION) in vec4 VertexAttribute_color;
layout(location = NORMAL_LOCATION) in vec3 VertexAttribute_normal;
layout(location = TEX_COORD_LOCATION) in vec2 VertexAttribute_texCoord;
layout(location = MODEL_MATRIX_LOCATION) in mat4 VertexAttribute_modelMat;