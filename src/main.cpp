#include <assert.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <TGUI/TGUI.hpp>
#include "Physics.h"
#include "constants.h"
#include "Game.h"

using namespace std;

void startGame(Game game, Physics& physics, tgui::Button::Ptr startButton, sf::Clock gameTimer);
void addCircle(Physics& physics);
bool started = false;

int main()
{
	bool ended = false;
	sf::Clock gameTime;
	float lastAddedTime = 0;
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
	tgui::Gui gui(window);
	// window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
	Physics physics(window);
	sf::Font font;
    font.loadFromFile("../fonts/Ubuntu-M.ttf");
    arma::arma_rng::set_seed_random();

	Game game(window, physics);

	auto layout = tgui::VerticalLayout::create();
	layout->setSize("25%", "15%");
	layout->setPosition(500 - 0.25*500, 100);
	gui.add(layout);
	
	auto startButton = tgui::Button::create();
	startButton->setText("Start");
	startButton->connect("pressed", startGame, std::ref(game), std::ref(physics), std::ref(startButton), std::ref(gameTime));
	startButton->connect("pressed", [&](){started = true;});
	layout->add(startButton);

	sf::Clock timer;
	float deltaTime;
    while (window.isOpen()) {
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
                window.close();
			gui.handleEvent(event);
		}

		window.clear();
		if(started){
			physics.update(deltaTime);
			physics.draw(deltaTime);
			game.loop();
		}
		gui.draw();
        window.display();
    }

    return 0;
}

void startGame(Game game, Physics& physics, tgui::Button::Ptr startButton, sf::Clock gameTimer){
	std::cout << "starting game" << std::endl;
	startButton->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.5));
	game.start();
	started = true;
}
