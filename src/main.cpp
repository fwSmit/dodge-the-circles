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

void startGame(Game& game, tgui::Button::Ptr startButton);
void addCircle(Physics& physics);
bool started = false;

int main()
{
	sf::Clock gameTime;
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
	startButton->connect("pressed", startGame, std::ref(game), std::ref(startButton));
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
			if (event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == sf::Mouse::Button::Left){
					game.mouseReleased();
				} 
			}
			gui.handleEvent(event);
		}

		window.clear(sf::Color(250, 250, 250));
		if(started){
			physics.update(deltaTime);
			physics.draw(deltaTime);
			game.loop(deltaTime);
		}
		gui.draw();
        window.display();
    }

    return 0;
}

void startGame(Game& game, tgui::Button::Ptr startButton){
	startButton->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.5));
	game.start();
}
