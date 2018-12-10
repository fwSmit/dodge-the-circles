#include <assert.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <TGUI/TGUI.hpp>
#include "Physics.h"
//#include "ProjectDodge.h"

using namespace std;

void resetGame(Physics& physics, tgui::Button::Ptr startButton, sf::Clock gameTimer);
void addCircle(Physics& physics);

int main()
{
	bool started = false;
	sf::Clock gameTime;
	float lastAddedTime = 0;
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
	tgui::Gui gui(window);
    //window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
	Physics physics(window);
	//ProjectDodge dodge(window);
    //window.setFramerateLimit(10);
	//physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-500, 0});
	sf::Font font;
    font.loadFromFile("../fonts/Ubuntu-M.ttf");
    arma::arma_rng::set_seed_random();

	//tgui::Button::Ptr startButton = tgui::Button::create("Start");
	//startButton->setSize("25%" , "15%");
	//startButton->setPosition("50%" , "50%");
	//gui.add(startButton);
	
	auto layout = tgui::VerticalLayout::create();
	layout->setSize("25%", "15%");
	layout->setPosition(500 - 0.25*500, 100);
	gui.add(layout);
	
	auto startButton = tgui::Button::create();
	startButton->setText("Start");
	startButton->connect("pressed", resetGame, std::ref(physics), std::ref(startButton), std::ref(gameTime));
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
		//dodge.loop();
		if(started && gameTime.getElapsedTime().asSeconds() - lastAddedTime > 4){
			addCircle(physics);
			lastAddedTime = gameTime.getElapsedTime().asSeconds();
		}
		physics.update(deltaTime);
		physics.draw(deltaTime);

		gui.draw();
        window.display();
    }

    return 0;
}

void resetGame(Physics& physics, tgui::Button::Ptr startButton, sf::Clock gameTimer){
	for(int i = 0; i < 3; i++){
		addCircle(physics);
	}
	startButton->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.5));
	gameTimer.restart();
}

void addCircle(Physics& physics){
	float radius = 15, speed = 300;
	arma::fvec2 bounds {500, 400};
	arma::fvec2 smallBounds {bounds[0]-2*radius, bounds[1]-2*radius};
		arma::fvec2 pos{static_cast<float>(arma::randu())*smallBounds[0] + radius, static_cast<float>(arma::randu())*smallBounds[1] + radius};
		arma::fvec2 vel{static_cast<float>(arma::randu())*100 - 50, static_cast<float>(arma::randu()) * 100 - 50};
		physics.addObject(pos,vel, radius);
}
