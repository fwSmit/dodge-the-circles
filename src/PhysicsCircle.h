#include "SFML/Graphics.hpp"
#include "functions.h"
#include "constants.h"
#include <functional>

class PhysicsCircle : public sf::CircleShape
{
    float mass = 1;
    sf::Clock lifeTime;
    bool oldEnough = 0;
	float maxSpeed = 10;
	float CharacterRadius = 30;
public:
	functions* func;
	//sf::Clock& timer;
	
	PhysicsCircle(){}
	
    PhysicsCircle(functions& _func);

    float getLifeTime()const
    {
        return lifeTime.getElapsedTime().asSeconds();
    }

    void setPos(arma::fvec2& position)
    {
        setPosition(position[0], position[1]);
    }

    bool getOldEnough() const
    {
        return oldEnough;
    }

    arma::fvec2 getPos()
    {
		return op::toArma(getPosition());
    }

    bool getHit(PhysicsCircle& other);

    void update(std::vector<PhysicsCircle>& enemies);

    void myMove(arma::fvec2 velocity)
    {
        //std::cout << velocity[0] * timer.getElapsedTime().asMilliseconds() * 0.06 << std::endl;

		//velocity gets higher over time
        //move(velocity[0] * timer.getElapsedTime().asMilliseconds() * 0.06, velocity[1] * timer.getElapsedTime().asMilliseconds() * 0.06);
		move(velocity[0] * func->getElapsedTime() * 0.06, velocity[1] * func->getElapsedTime() * 0.06);
    }

    void clampInScreen()
    {
        float value_x = func->clamp(getPosition().x, getRadius(), func->getWindowSize().x - getRadius());
        float value_y = func->clamp(getPosition().y, getRadius(), func->getWindowSize().y - getRadius());
        setPosition(value_x, value_y);
    }

    void setRad(float radius)
    {
        setRadius(radius);
        mass = arma::datum::pi * pow(radius, 2);
        setOriginCenter();
    }

    void setOriginCenter()
    {
        setOrigin(getRadius(), getRadius());
    }

    void reset();

    float getMass() const
    {
        return mass;
    }

	void moveWithCurrentVel(){
		myMove(vel);
	}

	float getRad(){
		return op::toArma(getRadius());
	}

    arma::fvec2 vel;
};
