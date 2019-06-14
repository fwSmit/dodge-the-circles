#include "Game.h"
#include "constants.h"

Game::Game(sf::RenderWindow& _window, Physics& _physics) : window(_window), func(_window), Player(func), physics(_physics)
{
    font.loadFromFile("../fonts/Ubuntu-M.ttf");
    arma::arma_rng::set_seed_random();
    Player.setFillColor(sf::Color::Green);
    //debugInit();
    // alpha 120
}

void Game::loop(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
	if(!func.isGameOver())
	{
		if (std::round(surviveTimer.getElapsedTime().asSeconds()) > lastSecond) {
			lastSecond = std::round(surviveTimer.getElapsedTime().asSeconds());
			if (int(std::round(surviveTimer.getElapsedTime().asSeconds())) % enemySpawnTime == 0) {
				// spawn new enemy
				addCircle();
			}
		}

		Player.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		Player.clampInScreen();
		if(isPlayerVulnerable()){
			Player.setFillColor(sf::Color::Green);
		}
		else{
			Player.setFillColor(sf::Color(0, 150, 0));
		}
		window.draw(Player);
		if(physics.getNumObjects() > number_start_enemies)
		{
			if(isEnemyAdded()){
				physics.setObjectColor(physics.getNumObjects()-1, sf::Color::Blue);
			}
			else{
				physics.setObjectColor(physics.getNumObjects()-1, sf::Color(0, 0, 150));
			}
		}
	}
	//score.setString(std::to_string(surviveTime.asSeconds()));
	// window.clear(func.isGameOver()?sf::Color(100, 10, 10, 100):sf::Color());
	//window.draw(sf::Text(sf::String(std::to_string(lastSecond)), font));
	// using stringstream, because std::to_string doesn't compile

	if(!func.isGameOver() && isPlayerVulnerable())
	{
		size_t num_enemies = physics.getNumObjects();
		if(!isEnemyAdded()){
			num_enemies--;
		}
		for(size_t i = 0; i < num_enemies; i++){
			// float rad1 = Player.getRadius();
			float rad1 = Player.getRad();
			float rad2 = physics.getObject(i).getRadius();
			float distance = func.distance(Player.getPos(), physics.getObject(i).getPos());
			// std::cout << distance << std::endl;
			if(distance <= (rad1+rad2)){
				// std::cout << "Hit" << std::endl;
				float overlap = (rad1+rad2) - distance + 0.01;
				std::cout << overlap << std::endl;
				arma::fvec2 delta_norm = (Player.getPos() - physics.getObject(i).getPos());
				delta_norm = arma::normalise(delta_norm);
				std::cout << delta_norm << std::endl;
				arma::fvec2 newPos = Player.getPos() + delta_norm * overlap;
				std::cout << newPos << std::endl;
				Player.setPos(newPos);
				func.setGameOver(true);
				for(int i = physics.getNumLines() - 1; i>= 0; i--){
					physics.removeLine(i);
				}
				float radius = Player.getRad();
				arma::fvec2 pos = Player.getPos();

				arma::fvec2 vel{0, 0};
				Circle object;
				object.setPos(pos);
				object.setVel(vel);
				object.setRadius(radius);
				physics.addObject(object, sf::Color::Green);
				break;
			}
		}
	}

	std::stringstream ss;
	if(highScore < lastSecond && !func.isGameOver()) {
		highScore = lastSecond;
		newHighScore = true;
	}
	if(!func.isGameOver()){
		currentScore = lastSecond;
	}
	ss << "score: " << currentScore << std::endl << "highscore: " << highScore << std::endl;// << "fps: " << 1/timer.getElapsedTime().asSeconds();

	if(newHighScore){
		ss << "new record" << std::endl;
	}
	if(func.isGameOver()) {
		// Player.setPosition(Player.getPosition().x, Player.getPosition().y + fallingVelocity);

		for(size_t i = 0; i < physics.getNumObjects(); i++){
			arma::fvec2 force = {0, 1000 * physics.getObject(i).getMass() * fallingAcceleration};
			physics.getObject(i).applyForce(force, deltaTime);
		}
		// fallingVelocity += fallingAcceleration;

	}

	if(func.isGameOver()) {
		std::string str = "click to restart";
		sf::Text clickToRestart(str, font, 100);
		clickToRestart.setFillColor(sf::Color::Black);
		// this moves the text to the center
		clickToRestart.setPosition(sf::Vector2f(func.getWindowSize())/2.f );
		sf::FloatRect textRect = clickToRestart.getLocalBounds();
		clickToRestart.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
		//clickToRestart.move(-0.25 * str.size() * clickToRestart.getCharacterSize(), -0.5 * clickToRestart.getCharacterSize());
		window.draw(clickToRestart);
	}
	func.update();
	sf::Text info(sf::String(ss.str()), font);
	info.setFillColor(sf::Color::Black);
	window.draw(info);
}

void Game::resetGame()
{
	func.setGameOver(false);
	physics.reset();
	for (size_t i = 0; i < number_start_enemies; i++) {
		addCircle();
	}
	surviveTimer.restart();
	lastSecond = 0;
	currentScore = 0;
	newHighScore = false;
}

void Game::start(){
	resetGame();
}

void Game::addCircle(){
	float radius = 40, speed = 300;
	arma::fvec2 bounds {500, 400};
	arma::fvec2 smallBounds {bounds[0]-2*radius, bounds[1]-2*radius};
	arma::fvec2 pos{static_cast<float>(arma::randu())*smallBounds[0] + radius, static_cast<float>(arma::randu())*smallBounds[1] + radius};
	arma::fvec2 vel{static_cast<float>(arma::randu())*speed, static_cast<float>(arma::randu())*speed};
	physics.addObject(pos,vel, radius);
	enterTimer.restart();
}

void Game::mouseReleased(){
	if(func.isGameOver()){
		resetGame();
	}
}

bool Game::isPlayerVulnerable(){
	return surviveTimer.getElapsedTime() > invulnerablePeriod;
}

bool Game::isEnemyAdded(){
	return enterTimer.getElapsedTime() > enemyInitTime;
}
