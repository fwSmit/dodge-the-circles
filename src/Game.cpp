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

void Game::loop()
{
		deltaTime = timer.restart().asSeconds();
        if (std::round(surviveTimer.getElapsedTime().asSeconds()) > lastSecond) {
            lastSecond = std::round(surviveTimer.getElapsedTime().asSeconds());
            //system("cls");
            //std::cout << lastSecond << std::endl;
            if (int(std::round(surviveTimer.getElapsedTime().asSeconds())) % enemySpawnTime == 0) {
				// spawn new enemy
				addCircle();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
		Player.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		Player.clampInScreen();
        window.draw(Player);
        //score.setString(std::to_string(surviveTime.asSeconds()));
        // window.clear(func.isGameOver()?sf::Color(100, 10, 10, 100):sf::Color());
        //window.draw(sf::Text(sf::String(std::to_string(lastSecond)), font));
        // using stringstream, because std::to_string doesn't compile
        std::stringstream ss;
        if(highScore < lastSecond && !func.isGameOver()) {
            highScore = lastSecond;
        }
        if(!func.isGameOver()){
            currentScore = lastSecond;
        }
        ss << "score: " << currentScore << std::endl << "highscore: " << highScore << std::endl;// << "fps: " << 1/timer.getElapsedTime().asSeconds();

        if(currentScore == highScore){
            ss << "new record" << std::endl;
        }
        if(func.isGameOver()) {
            const float fallingAcceleration = 0.2;
            Player.setPosition(Player.getPosition().x, Player.getPosition().y + fallingVelocity);

            //for(int i = 0; i < enemies.size(); i++) {
                //auto newPosition = enemies[i].getPosition();
                //newPosition.y += fallingVelocity;
                //enemies[i].setPosition(newPosition);
            //}

            fallingVelocity += fallingAcceleration;
            //ss << std::endl << "falling speed " << fallingVelocity << std::endl;

        }

        if(func.isGameOver()) {
            std::string str = "click to restart";
            sf::Text clickToRestart(str, font, 100);
            // this moves the text to the center
            clickToRestart.setPosition(sf::Vector2f(func.getWindowSize())/2.f );
			sf::FloatRect textRect = clickToRestart.getLocalBounds();
			clickToRestart.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
            //clickToRestart.move(-0.25 * str.size() * clickToRestart.getCharacterSize(), -0.5 * clickToRestart.getCharacterSize());
            window.draw(clickToRestart);
        }
        timer.restart();
		func.update();
        window.draw(sf::Text(sf::String(ss.str()), font));
        window.draw(sf::Text(sf::String(ss.str()), font));
}

void Game::resetGame()
{
	// std::vector<arma::fvec2> positions;
	// float radius = 10;
	// float radius_sq = radius*radius;
	// arma::fvec2 gameSize = op::toArma(func.getWindowSize());
	for (int i = 0; i < number_start_enemies; i++) {
		addCircle();
	}
	// for(auto& i : positions){
		// arma::fvec2 vel{static_cast<float>(arma::randu()), static_cast<float>(arma::randu())};
		// physics.addObject(i, 300 * vel);
	// }
	//physics.addObject(arma::fvec2{100, 100}, arma::fvec2{100, 100});
}

void Game::start(){
	resetGame();
}

void Game::addCircle(){
	float radius = 40, speed = 300;
	arma::fvec2 bounds {500, 400};
	arma::fvec2 smallBounds {bounds[0]-2*radius, bounds[1]-2*radius};
		arma::fvec2 pos{static_cast<float>(arma::randu())*smallBounds[0] + radius, static_cast<float>(arma::randu())*smallBounds[1] + radius};
		arma::fvec2 vel{static_cast<float>(arma::randu())*100 - 50, static_cast<float>(arma::randu()) * 100 - 50};
		physics.addObject(pos,vel, radius);
}
