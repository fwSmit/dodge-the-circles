#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>


class Circle;

namespace constants{
	const float scale = 2.f; // pixels / meter
}
namespace op{ // open for all classes
	sf::Vector2f toSf(arma::fvec2 vec);
	float toSf(float val);
	arma::fvec2 toArma(sf::Vector2f vec);
	arma::fvec2 toArma(sf::Vector2u vec);
	arma::fvec2 toArma(sf::Vector2i vec);
	float toArma(float val);
	void drawPoint(arma::fvec2 p, sf::RenderWindow& window);
	void drawPoint(arma::fvec2 p, sf::Color color, sf::RenderWindow& window);
	void drawArrow(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow& window);
	arma::fvec2 getParalel(arma::fvec2 start, arma::fvec2 paralelTo);
	sf::Vector2f getMousePos(sf::RenderWindow& window);
	bool isMouseInWindow(sf::RenderWindow& window);
	bool isMouseOnAnyWidget(tgui::Gui& gui, sf::RenderWindow& window);
	bool isCircleInBounds(Circle c);
	//float distance(arma::fvec2 a, arma::fvec2 b);
	//arma::fvec2 getIntersection(Line a, Line b);
}
