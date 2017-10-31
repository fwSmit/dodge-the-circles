#include "functions.h"

functions::functions(sf::RenderWindow& _window) : window(_window){
	
}

float functions::clamp(float value, float min, float max){
	return value < min ? min : value> max ? max : value;
}

float functions::distance(arma::fvec2 a, arma::fvec2 b){
	return arma::norm(a - b);
}

arma::fvec2 functions::getParalel(arma::fvec2 start, arma::fvec2 paralelTo){
	arma::fvec2 paralel = paralelTo * (arma::dot(paralelTo, start) / (pow(arma::norm(paralelTo), 2)));
	//arma::fvec2 perpendicular_i = start - paralel_i;
	return paralel;
}

float functions::getElapsedTime(){
	return elapsedTime;
}

void functions::update(){
	elapsedTime = timer.restart().asMilliseconds();
}
