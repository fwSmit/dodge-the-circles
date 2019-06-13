#include <SFML/Graphics.hpp>
#include "functions.h"
#include "PhysicsCircle.h"
#include "Physics.h"

class Game{
	public:
		Game(sf::RenderWindow& _window, Physics& physics);
		void loop(float deltaTime);
		void resetGame();
		void start();
	protected:

	private:
		void addCircle();
		sf::RenderWindow& window;
		sf::Clock timer;
		float deltaTime;
		Physics& physics;
		sf::Font font;
		PhysicsCircle Player;
		sf::Clock surviveTimer;
		functions func;
		int highScore = 0;
		int lastSecond = 0;
		int currentScore = 0;
		const size_t number_start_enemies = 3;
		unsigned int enemySpawnTime = 5;
		// makes all circles go down when the player is dead
		const float fallingAcceleration = 0.2;
		float fallingVelocity = 0;
		//std::vector<PhysicsCircle> enemies;

};
