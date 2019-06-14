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
		void mouseReleased();
	protected:

	private:
		void addCircle();
		sf::RenderWindow& window;
		Physics& physics;
		sf::Font font;
		PhysicsCircle Player;
		sf::Clock surviveTimer;
		sf::Clock enterTimer;
		functions func;
		int highScore = 0;
		int lastSecond = 0;
		int currentScore = 0;
		int enemySpawnTime = 3;
		const size_t number_start_enemies = 3;
		// makes all circles go down when the player is dead
		const float fallingAcceleration = 0.2;
		float fallingVelocity = 0;
		const sf::Time invulnerablePeriod = sf::seconds(1);
		const sf::Time  enemyInitTime = sf::seconds(1);
		bool isPlayerVulnerable();
		bool isEnemyAdded();
		bool newHighScore = false;
};
