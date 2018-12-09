#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include "ProjectDodge.h"










int main()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
	//Physics physics(window);
    window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
	ProjectDodge dodge(window);
    //window.setFramerateLimit(10);
	//physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-500, 0});
	sf::Clock timer;
	float deltaTime;
    while (window.isOpen()) {
		deltaTime = timer.restart().asSeconds();

		dodge.loop();

        window.display();
    }

    return 0;
}
