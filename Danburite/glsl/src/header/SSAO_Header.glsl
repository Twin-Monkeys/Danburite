//? #version 460 core

#ifndef __SSAO_HEADER__
#define __SSAO_HEADER__

#include "Constant_Header.glsl"

const uint NUM_SAMPLING_OFFSETS = 64U;
const vec3 samplingOffsets[NUM_SAMPLING_OFFSETS] = vec3[]
(
	vec3(.0214918f, -.0159405f, .0379622f),
	vec3(-.156152f, .68178f, .909513f),
	vec3(-.00206395f, .115187f, .380453f),
	vec3(-.247238f, -.348961f, .249308f),
	vec3(-.039954f, -.0339328f, .0179902f),
	vec3(.0708453f, -.111f, .0366819f),
	vec3(.0151294f, .484966f, .387933f),
	vec3(-.169316f, .0799916f, .136213f),
	vec3(-.068269f, .0746036f, .137039f),
	vec3(-.864923f, .0998464f, .202612f),
	vec3(-.321536f, .250458f, .113812f),
	vec3(-.607612f, -.111362f, .624294f),
	vec3(-.14436f, -.863276f, .257643f),
	vec3(-.037667f, .0130399f, .0384576f),
	vec3(.0366172f, .0962031f, .110615f),
	vec3(.00164531f, .00600619f, .00247094f),
	vec3(-.206996f, .0683046f, .468973f),
	vec3(-.0960114f, -.417282f, .457418f),
	vec3(.240628f, .258463f, .331718f),
	vec3(-.864285f, .108791f, .52979f),
	vec3(.114175f, -.129169f, .107654f),
	vec3(.219856f, -.0982413f, .125972f),
	vec3(.0455575f, .0174579f, .0365033f),
	vec3(.533741f, -.152661f, .289682f),
	vec3(-.0665292f, -.0603383f, .0525481f),
	vec3(.0770003f, -.0561081f, .0462088f),
	vec3(.703287f, -.100755f, .771936f),
	vec3(.0570977f, .213711f, .229705f),
	vec3(-.0623726f, -.0824762f, .0244276f),
	vec3(.300634f, .0753112f, .277814f),
	vec3(.0466734f, -.257472f, .238392f),
	vec3(-.550499f, -.620389f, .620124f),
	vec3(-.17908f, -.243905f, .155828f),
	vec3(-.269031f, -.434193f, .280269f),
	vec3(-.191634f, -.318363f, .503014f),
	vec3(-.282586f, -.112677f, .060878f),
	vec3(-.115809f, -.0677663f, .0962955f),
	vec3(.0449911f, .714421f, .281617f),
	vec3(-.223793f, .557052f, .286425f),
	vec3(-.0260023f, .00696147f, .00745168f),
	vec3(-.00193514f, -.00176478f, .00162055f),
	vec3(-.199008f, -.0849161f, .0722473f),
	vec3(-.431771f, -.836555f, .0963872f),
	vec3(-.166355f, -.033754f, .336053f),
	vec3(-.0101241f, -.0175617f, .021291f),
	vec3(.0758875f, -.0331909f, .0945982f),
	vec3(-.00488676f, -.0132709f, .470857f),
	vec3(-.0273696f, -.0310936f, .0574162f),
	vec3(.231239f, -.403661f, .912676f),
	vec3(.0482956f, .128284f, .176233f),
	vec3(.410876f, .0825508f, .161683f),
	vec3(-.121123f, .0216639f, .135975f),
	vec3(-.157254f, -.00741655f, .00968491f),
	vec3(-.271502f, -.414906f, .27431f),
	vec3(-.000301436f, .000639594f, .000728455f),
	vec3(-.383908f, -.20549f, .263826f),
	vec3(-.072219f, -.127649f, .0648401f),
	vec3(.248236f, .124709f, .133409f),
	vec3(-.0281643f, .217558f, .0915879f),
	vec3(.122526f, .091517f, .182504f),
	vec3(-.277167f, .0109572f, .154366f),
	vec3(.0111514f, -.0155473f, .0230265f),
	vec3(-.0276332f, .0344615f, .0983876f),
	vec3(-.247374f, .0380025f, .159054f)
);

const uint NUM_RANDOM_TANGENTS = 17U;
const vec3 randomTangents[NUM_RANDOM_TANGENTS] = vec3[]
(
	vec3(.462739f, -.343214f, -.81736f),
	vec3(-.0372106f, .919236f, -.391945f),
	vec3(.599796f, .800145f, -.00359915f),
	vec3(.150101f, -.495768f, -.855385f),
	vec3(-.670458f, .464551f, .578514f),
	vec3(-.49944f, -.704929f, -.503622f),
	vec3(-.720927f, -.612282f, .324615f),
	vec3(.315436f, .778031f, .543294f),
	vec3(-.949238f, -.313691f, .0233309f),
	vec3(.668673f, .534884f, -.516503f),
	vec3(.211839f, -.883652f, .417472f),
	vec3(.774629f, -.426939f, .466555f),
	vec3(.886179f, .0867163f, .455156f),
	vec3(-.96755f, .111694f, -.226653f),
	vec3(-.759838f, .59187f, -.268956f),
	vec3(.225786f, .468608f, -.854065f),
	vec3(-.172225f, .965488f, -.195376f)
);

mat3 SSAO_getRandomViewSpaceTBN(const ivec2 screenCoord, const vec3 viewSpaceNormal)
{
	const uint randomIdx = (uint(screenCoord.x + screenCoord.y) % NUM_RANDOM_TANGENTS);
	const vec3 randomTangent = randomTangents[randomIdx];

	vec3 viewSpaceTangent;

	const float tangentDotNormal = dot(randomTangent, viewSpaceNormal);
	if (abs(tangentDotNormal) < (1.f - EPSILON))
	{
		const vec3 projTanOntoNormal = (tangentDotNormal * viewSpaceNormal);
		viewSpaceTangent = normalize(randomTangent - projTanOntoNormal);
	}
	else
	{
		/*
			If randomTangent is parallel with viewSpaceNormal,
			set the viewSpaceTangent as a dummy perpendicular vector against viewSpaceNormal.
		*/
		viewSpaceTangent = normalize(vec3(0.f, viewSpaceNormal.z, -viewSpaceNormal.y));
	}

	const vec3 viewSpaceBitangent = cross(viewSpaceNormal, viewSpaceTangent);

	return mat3(viewSpaceTangent, viewSpaceBitangent, viewSpaceNormal);
}

float SSAO_getAmbientOcclusion(
	const ivec2 screenCoord, const mat4 viewMat, const mat4 projMat,
	const sampler2DRect worldSpacePosTex, const vec3 worldSpaceNormal)
{
	const float samplingDepthBias = .01f;
	const float samplingRadius = .5f;
	const vec2 screenSize = vec2(textureSize(worldSpacePosTex));

	const vec3 worldSpacePos = texelFetch(worldSpacePosTex, screenCoord).xyz;
	const vec3 viewSpacePos = (viewMat * vec4(worldSpacePos, 1.f)).xyz;

	// Assume a view matrix has no scaling factor.
	const vec3 viewSpaceNormal = (viewMat * vec4(worldSpaceNormal, 0.f)).xyz;

	const mat3 viewSpaceTBN = SSAO_getRandomViewSpaceTBN(screenCoord, viewSpaceNormal);

	float retVal = 0.f;
	for (uint samplingOffsetIter = 0U; samplingOffsetIter < NUM_SAMPLING_OFFSETS; samplingOffsetIter++)
	{
		const vec3 tangentSpaceSamplingOffset = samplingOffsets[samplingOffsetIter];
		const vec3 viewSpaceSamplingPos = (viewSpacePos + (viewSpaceTBN * tangentSpaceSamplingOffset));
		const vec4 clipSpaceSamplingPos = (projMat * vec4(viewSpaceSamplingPos, 1.f));

		vec2 screenSpaceSamplingCoord = (((clipSpaceSamplingPos.xy / clipSpaceSamplingPos.w) + 1.f) * .5f);
		screenSpaceSamplingCoord *= screenSize;

		const vec3 worldSpaceProjPos = texture(worldSpacePosTex, screenSpaceSamplingCoord).xyz;
		const float viewSpaceProjDepth = dot(vec3(viewMat[0][2], viewMat[1][2], viewMat[2][2]), worldSpaceProjPos);

		if (viewSpaceProjDepth > (viewSpaceSamplingPos.z + samplingDepthBias))
			retVal += 1.f;
	}

	retVal /= float(NUM_SAMPLING_OFFSETS);
	return retVal;
}

#endif