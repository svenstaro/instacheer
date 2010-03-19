#ifndef PARTICLEEMITTER_HPP_INCLUDED
#define PARTICLEEMITTER_HPP_INCLUDED

#include "sfml-particle/ParticleSystem.hpp"

class ParticleEmitter : public part::IParticleEmitter {
public:
	virtual ~ParticleEmitter();

protected:
	virtual void InitParticle(ParticlePtr particle);
};

#endif
