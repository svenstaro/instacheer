#ifndef PARTICLEAFFECTOR_HPP_INCLUDED
#define PARTICLEAFFECTOR_HPP_INCLUDED

#include "sfml-particle/ParticleSystem.hpp"

class ScaleInAffector : public part::IParticleAffector {
public:
	ScaleInAffector(float fadeTime, float beginScale, float endScale);

	void Update(part::CParticle *particle, float dt);

private:
	float mFadeTime;
	float mSpeed;
	float mMaxScale;
};

#endif
