//? #version 460 core

#ifndef __SSAO_HEADER__
#define __SSAO_HEADER__

#include "Constant_Header.glsl"

const vec3 samplingOffsets[] = vec3[]
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

#endif