#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Particle
{
public:
	Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, sf::IntRect aliveBounds, int radius, sf::Color color);

	void update(double deltaTime);
	bool isAlive();

	sf::Vector2f getPosition();
	int getRadius();
	sf::Color getColor();

private:
	double x;
	double y;
	double xVelocity;
	double yVelocity;
	double gravity;

	bool alive = true;
	sf::IntRect bounds;

	int radius;
	sf::Color color;
};

#endif
