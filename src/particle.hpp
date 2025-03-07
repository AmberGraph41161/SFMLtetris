#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Particle
{
public:
	Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, sf::IntRect aliveBounds);

	void update(double deltaTime);
	bool isAlive();

	sf::Vector2f getPosition();

private:
	double x;
	double y;
	double xVelocity;
	double yVelocity;
	double gravity;

	bool alive = true;
	sf::IntRect bounds;
};

#endif
