#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SFML/Graphics.hpp"
#define ARMA_DONT_USE_BLAS
#include <armadillo>
#include <functional>

class functions{
	float elapsedTime = 0;
	std::reference_wrapper<sf::RenderWindow> window;
	sf::Clock timer;
	bool gameOver = 0;
	float startingRestTime = 0.5;

public:
	functions(sf::RenderWindow& _window);
	float clamp(float value, float min, float max);
	float distance(arma::fvec2 a, arma::fvec2 b);
	bool isGameOver(){ return gameOver; }
	void setGameOver(bool value) { gameOver = value; } 
	
	float getStartingRestTime(){ return startingRestTime; } 
	void setStartingRestTime(float time) { startingRestTime = time; } 


	sf::Vector2u getWindowSize(){
		return window.get().getSize();
	}

	// returns part of vector start which is paralel to paralelTo
	arma::fvec2 getParalel(arma::fvec2 start, arma::fvec2 paralelTo);
	float getElapsedTime();
	void update();
	sf::RenderWindow& getWindow(){ return window.get(); }
};
#endif // FUNCTIONS_H
