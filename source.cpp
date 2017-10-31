#include <assert.h>

#define convertToString(x) #x

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include <SFML/Main.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <numeric>
#include <iomanip>
#include "PhysicsCircle.h"

#include "functions.h"
#include <string>
#include <algorithm>

int highScore = 0;
int lastSecond = 0;
int currentScore = 0;
const size_t number_start_enemies = 6;
unsigned int enemySpawnTime = 10;
sf::Clock timer;
// makes all circles go down when the player is dead
float fallingVelocity = 0;
std::vector<PhysicsCircle> enemies;
sf::ContextSettings settings;

sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
functions func(window);

sf::Clock surviveTimer;
float startingRestTime = 0.5;


void initialize(PhysicsCircle& enemy)
{
    enemy.setFillColor(sf::Color::Red);
    enemy.setRad(CharacterRadius/*arma::randu() * 40 + 20*/);
    //printf("size x %d, y %d", func.getWindowSize().x, func.getWindowSize().y);
    //std::cout << position << std::endl;

    arma::fvec2 position(arma::fill::randu);
    position[0] *= func.getWindowSize().x - 2 * enemy.getRadius();
    position[1] *= func.getWindowSize().y - 2 * enemy.getRadius();
    position += enemy.getRadius();
    enemy.setPos(position);


    // make sure they don't collide at the start
    /*
    bool AreColliding;
    do {
    	AreColliding = 0;
    	for (auto& i : enemies) {
    			bool BoxHit = enemy.getGlobalBounds().intersects(i.getGlobalBounds());
    			if (BoxHit) {
    				AreColliding = true;
    				//std::cout << "still colliding" << std::endl;
    				//std::cout << enemies.size() << std::endl;
    			}
    	}
    } while (AreColliding);*/
}

// player character
PhysicsCircle Player(func);

void resetGame()
{
    enemies.clear();
    enemies.resize(number_start_enemies);
    for (int i = 0; i < number_start_enemies; i++) {
        bool AreColliding;
        PhysicsCircle temp(func);
        do {
            initialize(temp);
            AreColliding = 0;
            for (int j = 0; j < i; j++) {
                bool BoxHit = temp.getGlobalBounds().intersects(enemies[j].getGlobalBounds());
                if (BoxHit) {
                    AreColliding = true;
                    //std::cout << "still colliding" << std::endl;
                }
            }
        } while (AreColliding);
        enemies[i] = temp;
    }
}


void debugInit()
{
    enemies.resize(2);
    arma::fvec2 temp0 { 100, 80};
    enemies[0].setPos(temp0);
    arma::fvec2 temp1 { 400, 100 };
    enemies[1].setPos(temp1);
    enemies[0].vel = arma::fvec2{ 0.4f, 0 };
    enemies[1].vel = arma::fvec2{ 0, 0 };
    startingRestTime = 0;
}


int main()
{
    sf::Font font;
    font.loadFromFile("../fonts/Ubuntu-M.ttf");
    sf::Text test(sf::String("asdfjk"), font);
    arma::arma_rng::set_seed_random();
    Player.setFillColor(sf::Color::Green);
    //debugInit();
    // alpha 120
    resetGame();
    window.setMouseCursorVisible(0);
    window.setVerticalSyncEnabled(1);
    //window.setFramerateLimit(10);
    while (window.isOpen()) {
        if (std::round(surviveTimer.getElapsedTime().asSeconds()) > lastSecond) {
            lastSecond = std::round(surviveTimer.getElapsedTime().asSeconds());
            //system("cls");
            //std::cout << lastSecond << std::endl;
            if (int(std::round(surviveTimer.getElapsedTime().asSeconds())) % enemySpawnTime == 0) {
                PhysicsCircle newEnemy(func);
                initialize(newEnemy);
                enemies.push_back(newEnemy);
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
        window.draw(Player);
        for (auto& i : enemies) {
            Player.setFillColor(sf::Color(Player.getFillColor().r, Player.getFillColor().g, Player.getFillColor().b, 255));
            if (i.getLifeTime() > startingRestTime) {
                if (Player.getGlobalBounds().intersects(i.getGlobalBounds())) {
                    if (i.getHit(Player)) {
                        func.setGameOver(true);
                    }
                }
            }
            i.update(enemies);
            window.draw(i);
            //i.setFillColor(sf::Color::Red);
        }

        for (int i = 0; i < enemies.size()-1; i++) {
            for (int j = i + 1; j < enemies.size(); j++) {
                if (enemies[i].getOldEnough() && enemies[j].getOldEnough()) {
                    bool BoxHit = enemies[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds());
                    if (BoxHit) {
                        if (enemies[i].getHit(enemies[j])) {
                            //enemies[i].setFillColor(sf::Color::Green);
                            //enemies[j].setFillColor(sf::Color::Green);
                            arma::fvec2 oldVel_i = enemies[i].vel;
                            arma::fvec2 oldVel_j = enemies[j].vel;
                            arma::fvec2 deltaPos_i = enemies[i].getPos() - enemies[j].getPos();
                            arma::fvec2 deltaPos_j = enemies[j].getPos() - enemies[i].getPos();
                            //std::cout << deltaPos_i << std::endl << deltaPos_j << std::endl;
                            arma::fvec2 paralel_i = func.getParalel(enemies[i].vel, deltaPos_i);
                            arma::fvec2 paralel_j = func.getParalel(enemies[j].vel, deltaPos_j);
                            //std::cout << paralel_i << std::endl;
                            arma::fvec2 perpendicular_i = enemies[i].vel - paralel_i;
                            arma::fvec2 perpendicular_j = enemies[j].vel - paralel_j;
                            //std::cout << perpendicular_i << std::endl;
                            //std::cout << enemies[i].vel << std::endl;
                            //std::cout << perpendicular_i + paralel_i << std::endl;

                            arma::fvec2 newVel_i;
                            arma::fvec2 newVel_j;
                            newVel_i = (paralel_i * (enemies[i].getMass() - enemies[j].getMass()) + (2 * enemies[j].getMass() * paralel_j)) / (enemies[i].getMass() + enemies[j].getMass());
                            newVel_j = (paralel_j * (enemies[j].getMass() - enemies[i].getMass()) + (2 * enemies[i].getMass() * paralel_i)) / (enemies[j].getMass() + enemies[i].getMass());
                            newVel_i += perpendicular_i;
                            newVel_j += perpendicular_j;

                            enemies[i].vel = newVel_i;
                            enemies[j].vel = newVel_j;
							enemies[i].moveWithCurrentVel();
							enemies[j].moveWithCurrentVel();
                        }
                    }
                    if (enemies[i].getHit(enemies[j])) {
                        //enemies[i].setFillColor(sf::Color::Blue);
                        //enemies[j].setFillColor(sf::Color::Blue);
                    }
                }
            }
        }
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

            for(int i = 0; i < enemies.size(); i++) {
                auto newPosition = enemies[i].getPosition();
                newPosition.y += fallingVelocity;
                enemies[i].setPosition(newPosition);
            }

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
        window.draw(sf::Text(sf::String(ss.str()), font));
        window.draw(sf::Text(sf::String(ss.str()), font));

        // player died
        // this makes it fall



        //Player.update();
        //std::cout << timer.getElapsedTime().asSeconds()<< std::endl;
        timer.restart();
        window.display();
		func.update();
        //std::cout << timer.restart().asMilliseconds() << std::endl;
    }

    return 0;
}
