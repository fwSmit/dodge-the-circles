#ifndef PROJECT_DODGE_H
#define PROJECT_DODGE_H

#include "Project.h"
#include "TGUI/TGUI.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "functions.h"
#include "PhysicsCircle.h"

class CollisionHandler;

class ProjectDodge : Project
{
	public:
		ProjectDodge(sf::RenderWindow& _window);
		virtual ~ProjectDodge();
		void loop();
		void handleEvent(sf::Event event);
		void resetGame();
	protected:

	private:
		Physics physics;
		sf::Font font;
		PhysicsCircle Player;
		sf::Clock surviveTimer;
		functions func;
		int highScore = 0;
		int lastSecond = 0;
		int currentScore = 0;
		const size_t number_start_enemies = 6;
		unsigned int enemySpawnTime = 10;
		sf::Clock timer;
		// makes all circles go down when the player is dead
		float fallingVelocity = 0;
		std::vector<PhysicsCircle> enemies;

		void initializeEnemy(PhysicsCircle& enemy);
		void debugInit();
};

#endif // PROJECT_DODGE_H
