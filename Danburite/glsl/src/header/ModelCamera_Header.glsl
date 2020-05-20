//? #version 460 core

#ifndef __MODEL_CAMERA_HEADER__
#define __MODEL_CAMERA_HEADER__

#include "Camera_Header.glsl"
#include "Model_Header.glsl"

mat4 ModelCamera_getModelViewProjMatrix(mat4 modelMat)
{
	return (camera.projMat * camera.viewMat * modelMat);
}

mat4 ModelCamera_getViewProjMatrixWithoutTranslation()
{
	// Remove translation
	return (camera.projMat * mat4(mat3(camera.viewMat)));
}

vec4 ModelCamera_getNDCPosition(mat4 modelMat, const vec3 localPos)
{
	return (ModelCamera_getModelViewProjMatrix(modelMat) * vec4(localPos, 1.f));
}

#endif