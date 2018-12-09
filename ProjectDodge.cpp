#include "ProjectDodge.h"

ProjectDodge::ProjectDodge(sf::RenderWindow& _window) : Project(_window), func(_window), Player(func), physics(window)
{
    font.loadFromFile("../fonts/Ubuntu-M.ttf");
    arma::arma_rng::set_seed_random();
    Player.setFillColor(sf::Color::Green);
    //debugInit();
    // alpha 120
    resetGame();
}

ProjectDodge::~ProjectDodge()
{
	//dtor
}

void ProjectDodge::loop()
{
		deltaTime = timer.restart().asSeconds();
        if (std::round(surviveTimer.getElapsedTime().asSeconds()) > lastSecond) {
            lastSecond = std::round(surviveTimer.getElapsedTime().asSeconds());
            //system("cls");
            //std::cout << lastSecond << std::endl;
            if (int(std::round(surviveTimer.getElapsedTime().asSeconds())) % enemySpawnTime == 0) {
                PhysicsCircle newEnemy(func);
                //initializeEnemy(newEnemy);
                //enemies.push_back(newEnemy);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                if(!func.isGameOver()) {
                    Player.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                    Player.clampInScreen();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    func.setGameOver(0);
                    fallingVelocity = 0;
                    resetGame();
                    lastSecond = 0;
                    surviveTimer.restart();
                    //debugInit();
                }
                /*if (event.mouseButton.button == sf::Mouse::Button::Right) {
                	func.setGameOver(false);
                	//std::cout << sf::Mouse::getPosition(window).x << std::endl << sf::Mouse::getPosition(window).y << std::endl << Player.getPos() << std::endl;
                }*/
            }
        }
        //score.setString(std::to_string(surviveTime.asSeconds()));
        window.clear(func.isGameOver()?sf::Color(100, 10, 10, 100):sf::Color());
		physics.update(deltaTime);
		physics.draw(deltaTime);
        window.draw(Player);
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

void ProjectDodge::handleEvent(sf::Event event){
}

void ProjectDodge::resetGame()
{
	std::vector<arma::fvec2> positions;
	float radius = 10;
	float radius_sq = radius*radius;
    for (int i = 0; i < number_start_enemies; i++) {
		arma::fvec2 pos;
		bool intersects = true;
		//while(intersects){
			//pos = arma_rng::randu<arma::fvec2>();
			//intersects = arma::accu(arma::pow(pos-i, 2)) < radius_sq;
		//}
		pos = arma::fvec2{50, 50};
		positions.push_back(pos);
    }
	for(auto& i : positions){
		arma::fvec2 vel{static_cast<float>(arma::randu()), static_cast<float>(arma::randu())};
		physics.addObject(i, 300 * vel);
	}
	//physics.addObject(arma::fvec2{100, 100}, arma::fvec2{100, 100});
}
