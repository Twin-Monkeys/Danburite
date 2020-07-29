#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"
#include "header/Animation_Header.glsl"
#include "header/LightPrePass_Header.glsl"
#include "header/Fullscreen_Header.glsl"

void main()
{
	const uint lightVolumeType = LightPrePass_getLightVolumeType();

	if (lightVolumeType == LIGHT_VOLUME_TYPE_FULLSCREEN)
	{
		gl_Position = Fullscreen_getPosition(gl_VertexID);
	}
	else if (lightVolumeType == LIGHT_VOLUME_TYPE_GEOMETRY)
	{
		const mat4 modelMat = Animation_getAnimatedModelMatrix(
			VertexAttribute_modelMat, VertexAttribute_boneIndices, VertexAttribute_boneWeights);

		gl_Position = ModelCamera_getNDCPosition(modelMat, VertexAttribute_pos);

		// To prevent clipping light volume
		gl_Position.z = 0.f;
	}
} 