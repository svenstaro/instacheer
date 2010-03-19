#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <boost/cstdint.hpp>

#include <string>
#include <iostream>

#include "ParticleEmitter.hpp"
#include "ParticleAffector.hpp"

//Some convenient defines
#define PI 3.141592f
#define WIDTH 500
#define HEIGHT 300
#define DURATION 5
#define TEXT "LOLOMFG"

int main(int argc, char *argv[]) {
	std::string achievement = TEXT;

	sf::VideoMode VideoMode;
	VideoMode.GetDesktopMode();
	uint16_t posx = sf::VideoMode::GetDesktopMode().Width - WIDTH;
	uint16_t posy = sf::VideoMode::GetDesktopMode().Height - HEIGHT;
	
	sf::RenderWindow App(sf::VideoMode(WIDTH, HEIGHT), "Achievements", sf::Style::None);
	App.SetFramerateLimit(60);
	App.SetPosition(posx, posy);

	sf::Font Font;
	if(!Font.LoadFromFile("../font/LiberationSans-Bold.ttf"))
		return EXIT_FAILURE;
	sf::String Text("Achieved "+achievement, Font, 30);
	Text.SetPosition((WIDTH - Text.GetRect().GetWidth()) / 2, 
					(HEIGHT - Text.GetRect().GetHeight()) / 2);

	sf::Clock Clock;

	sf::Randomizer::SetSeed((unsigned int)time(NULL));
 
	//Initialize a particle system
	//Load up a particle image
	sf::Image ParticleImg;
	if(!ParticleImg.LoadFromFile("../gfx/star_blue.png")) 
		return EXIT_FAILURE;
	//So we whant to have a nice scale in effect on our particle system
	//Lets create a scale in affector
	ScaleInAffector scale_in(0.1f, 0.f, 1.f);
	//Create a instance of the Emitter1ter we just made
	ParticleEmitter Emitter1;
	Emitter1.SetColorRandom();
	Emitter1.SetMaterial(&ParticleImg);
	Emitter1.SetEmissionRate(0.02f, 10);
	Emitter1.SetMaxParticles(500);
	Emitter1.SetLiveTime(0.8f, 0.4f);
	Emitter1.SetInitialDimensions(12.f, 12.f);
	Emitter1.SetRotationSpeed(PI * 100);
	Emitter1.AddAffector(&scale_in);
	Emitter1.Init();
 
	//Let's copy our newly created Emitter
	ParticleEmitter Emitter2(Emitter1);
	Emitter2.SetOffset(sf::Vector2f(-100.f, 0));
	//when we copy the new system will share the same particles as the one it copied from, so to give it it's own pool of particles call Init() again
	Emitter2.Init();

	ParticleEmitter Emitter3(Emitter1);
	Emitter3.SetOffset(sf::Vector2f(100.f, 0));
	Emitter3.Init();
 
	//Finally we create a particle system with our Emitters :)
	part::CParticleSystem PartSys;
	PartSys.AddEmitter(&Emitter1);
	PartSys.AddEmitter(&Emitter2);
	PartSys.AddEmitter(&Emitter3);
	PartSys.SetPosition(Text.GetPosition().x + (Text.GetRect().GetWidth() / 2),
						Text.GetPosition().y + (Text.GetRect().GetHeight() / 2));
	PartSys.Rotate(180);

	sf::SoundBuffer Buffer;
	if(!Buffer.LoadFromFile("../snd/crowdcheer.ogg"))
		return EXIT_FAILURE;

	sf::Sound Sound;
	Sound.SetBuffer(Buffer);

	Sound.Play();
	while(Clock.GetElapsedTime() < DURATION) {
		App.Clear();

		float dt = App.GetFrameTime();
		//PartSys.Rotate(30*dt);

		PartSys.Update(App.GetFrameTime());
		App.Draw(PartSys);
		App.Draw(Text);
		App.Display();
	}
	return EXIT_SUCCESS;
}

