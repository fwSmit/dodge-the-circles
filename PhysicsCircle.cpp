#include "PhysicsCircle.h"


PhysicsCircle::PhysicsCircle(functions& _func) : func(_func)
    {
        reset();
        setRad(CharacterRadius);
        setOriginCenter();
        lifeTime.restart();
    }

    bool PhysicsCircle::getHit(PhysicsCircle& other)
    {
        if (&other != this) {
            return func.get().distance(other.getPos(), getPos()) <= getRadius() + other.getRadius();
        } else {
            //std::cout << "testing yourself" << std::endl;
        }
        return 0;
    }

    void PhysicsCircle::update(std::vector<PhysicsCircle>& enemies)
    {
        if (oldEnough) {
            auto position = getPosition();
            if (position.x + getRadius() > func.get().getWindowSize().x || position.x - getRadius() < 0) {
                vel[0] = -vel[0];
                if(!func.get().isGameOver()) clampInScreen();
                //std::cout << "x out of bounds" << std::endl;
            }
            if (position.y + getRadius() > func.get().getWindowSize().y || position.y - getRadius() < 0) {
                vel[1] = -vel[1];
                if(!func.get().isGameOver()) clampInScreen();
                //std::cout << "y out of bounds" << std::endl;
            }
			moveWithCurrentVel();
        } else {
            if (getLifeTime() > startingRestTime) {
                bool hit = 0;
                for (auto& i : enemies) {
                    if (getHit(i)) {
                        hit = true;
                        break;
                    }
                }
                oldEnough = !hit;
            }
        }
    }


    void PhysicsCircle::reset()
    {
        float rotation = arma::randu()*arma::fdatum::pi * 2;
        float speed = maxSpeed;//(arma::randu()+0.5*maxSpeed);
        //std::cout << "rotation " << rotation/ (arma::fdatum::pi * 2) * 360 << std::endl;
        //std::cout << "speed " << speed << std::endl;
        vel[0] = cos(rotation)*speed;
        vel[1] = sin(rotation)*speed;
    }
