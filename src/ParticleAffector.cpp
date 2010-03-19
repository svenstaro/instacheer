#include "ParticleAffector.hpp"

ScaleInAffector::ScaleInAffector(float fadeTime, float beginScale, float endScale) {
	mFadeTime = fadeTime;
	mSpeed = 0;
	mMaxScale = endScale;
	float scaleDif = mMaxScale - beginScale;
	mSpeed = scaleDif/mFadeTime;
}

void ScaleInAffector::Update(part::CParticle *particle, float dt) {
	//Only scale during the timespan we set in the beginning
	if(particle->GetStartLiveTime()-mFadeTime < particle->GetLiveTime())
	{
		//Scale acording to our speed
		particle->SetScale(particle->GetScale() + mSpeed*dt);
		//Just a safety check so we don't go over the wanted scale.
		if(particle->GetScale() > mMaxScale) 
			particle->SetScale(mMaxScale);
	}
}
