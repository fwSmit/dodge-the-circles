#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include <SFML/Main.hpp>
#include <SFML/Config.hpp>
#include "Physics.h"
//#include "ProjectDodge.h"
//#include <iostream>
//#include <numeric>
//#include <iomanip>
//#include "PhysicsCircle.h"

//#include "functions.h"
//#include <string>
//#include <algorithm>










int main()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
	Physics physics(window);
    window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
	//ProjectDodge dodge(window);
    //window.setFramerateLimit(10);
	physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-500, 0});
	sf::Clock timer;
	float deltaTime;
    while (window.isOpen()) {
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		physics.update(deltaTime);
		physics.draw(deltaTime);
        // player died
        // this makes it fall


		//dodge.loop();

        //Player.update();
        //std::cout << timer.getElapsedTime().asSeconds()<< std::endl;
        window.display();
        //std::cout << timer.restart().asMilliseconds() << std::endl;
    }

    return 0;
}
