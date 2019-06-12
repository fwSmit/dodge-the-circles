#include <SFML/Graphics.hpp>
#include "functions.h"
#include "PhysicsCircle.h"
#include "Physics.h"

class Game{
	public:
		Game(sf::RenderWindow& _window);
		void loop();
		void resetGame();
		void start();
	protected:

	private:
		void addCircle();
		sf::RenderWindow& window;
		sf::Clock timer;
		float deltaTime;
		Physics physics;
		sf::Font font;
		PhysicsCircle Player;
		sf::Clock surviveTimer;
		functions func;
		int highScore = 0;
		int lastSecond = 0;
		int currentScore = 0;
		const size_t number_start_enemies = 6;
		unsigned int enemySpawnTime = 1;
		// makes all circles go down when the player is dead
		float fallingVelocity = 0;
		//std::vector<PhysicsCircle> enemies;

};
