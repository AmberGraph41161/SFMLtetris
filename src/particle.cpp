#include "particle.hpp"
#include <SFML/System/Vector2.hpp>

Particle::Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, sf::IntRect aliveBounds)
	: x(startX), y(startY), xVelocity(startXVelocity), yVelocity(startYVelocity), gravity(setGravity), bounds(aliveBounds)
{
}

void Particle::update(double deltaTime)
{
	yVelocity += gravity * deltaTime;

	x += xVelocity * deltaTime;
	y += yVelocity * deltaTime;

	if(
		x <= bounds.position.x ||
		x >= bounds.size.x ||
		y <= bounds.position.y ||
		y >= bounds.size.y
	)
	{
		alive = false;
	}
}

bool Particle::isAlive()
{
	return alive;
}

sf::Vector2f Particle::getPosition()
{
	return sf::Vector2f(x, y);
}
