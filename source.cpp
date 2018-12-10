#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <TGUI/TGUI.hpp>
#include "Physics.h"
//#include "ProjectDodge.h"

int main()
{
	bool started = false;
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
	tgui::Gui gui(window);
    //window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
	Physics physics(window);
	//ProjectDodge dodge(window);
    //window.setFramerateLimit(10);
	physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-500, 0});
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
	startButton->connect("pressed", resetGame());
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
		physics.update(deltaTime);
		physics.draw(deltaTime);

		gui.draw();
        window.display();
    }

    return 0;
}

void resetGame(){
	
}
