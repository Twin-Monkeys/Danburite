//? #version 460 core

#ifndef __MODEL_HEADER__
#define __MODEL_HEADER__

vec3 Model_getWorldPosition(mat4 modelMat, vec3 localPos)
{
	return (modelMat * vec4(localPos, 1.f)).xyz;
}

mat3 Model_getNormalModelMatrix(mat4 modelMat)
{
	return transpose(inverse(mat3(modelMat)));
}

vec3 Model_getWorldNormal(mat4 modelMat, vec3 localNormal)
{
	// Model Matrix에는 Scaling 요소가 있으므로 normalize가 필요함.
	return normalize(Model_getNormalModelMatrix(modelMat) * localNormal);
}

#endif