#include "ParticleEmitter.hpp"

#define PI 3.141592f

ParticleEmitter::~ParticleEmitter() {}
 
void ParticleEmitter::InitParticle(ParticlePtr particle) {
	//Calculate world position of the particle
	sf::Vector2f ws_pos = mPos + mPositionOffset;
	//Provide an initial direction
	sf::Vector2f dir(0.f, 1.f);

	//Get a random angle between the given extremes
	float angle_variation_min = mAngleRangeMin*(PI/180);
	float angle_variation_max = mAngleRangeMax*(PI/180);
	float angle = sf::Randomizer::Random(angle_variation_min, angle_variation_max);
	//Get a direction vector from the angle and initial direction
	float cos_val = cosf(angle);
	float sin_val = sinf(angle);
	dir = sf::Vector2f(dir.x * cos_val - dir.y * sin_val, dir.y * cos_val + dir.x * sin_val);
	//Since we have a normalized vector to begin with we do not need to normalize it after theese calculations.

	//Let's give a little variation to our speed value
	float speed_var = 40.f;
	float speed = 150.f;
	speed = sf::Randomizer::Random(speed-speed_var, speed+speed_var);

	//Use the provided base function to get a random color
	sf::Color clr = this->RandomiseColor();

	//Since we will use a scale in affector we set the starting scale to 0
	float scale = 0.f;

	//Finally we initialize our particle :)
	particle->Init(ws_pos, dir, speed, sf::Randomizer::Random(this->mLiveTime-mLiveTimeVariation, this->mLiveTime+mLiveTimeVariation), clr, 0.f, scale);
}
