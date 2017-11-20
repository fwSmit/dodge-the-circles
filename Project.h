#ifndef PROJECT_H
#define PROJECT_H

#include <SFML/Graphics.hpp>

class CollisionHandler;

class Project
{
    public:
        Project(sf::RenderWindow& _window);
        virtual ~Project();
        void loop();

    protected:
		sf::RenderWindow& window;

    private:

};

#endif // PROJECT_H
