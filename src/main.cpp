#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <boost/cstdint.hpp>

#include <string>
#include <iostream>

#define WIDTH 500
#define HEIGHT 500
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
	Text.SetPosition((WIDTH / 2), (HEIGHT / 2));

	sf::Clock Clock;

	sf::SoundBuffer Buffer;
	if(!Buffer.LoadFromFile("../snd/crowdcheer.ogg"))
		return EXIT_FAILURE;

	sf::Sound Sound;
	Sound.SetBuffer(Buffer);

	Sound.Play();
	while(Clock.GetElapsedTime() < DURATION) {
		App.Clear();

		//PartSys.Update(App.GetFrameTime());
		App.Draw(Text);
		App.Display();
	}
	return EXIT_SUCCESS;
}

