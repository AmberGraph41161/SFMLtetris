#include "particle.hpp"
#include <SFML/System/Vector2.hpp>

Particle::Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, sf::IntRect aliveBounds, int radius, sf::Color color)
	: x(startX), y(startY), xVelocity(startXVelocity), yVelocity(startYVelocity), gravity(setGravity), bounds(aliveBounds), radius(radius), color(color)
{
}

void Particle::update(double deltaTime)
{
	//https://youtu.be/yGhfUcPjXuE?feature=shared
	//^^^ or something like that lol
	yVelocity += gravity * deltaTime * 0.5;
	x += xVelocity * deltaTime;
	y += yVelocity * deltaTime;
	yVelocity += gravity * deltaTime * 0.5;

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

int Particle::getRadius()
{
	return radius;
}

sf::Color Particle::getColor()
{
	return color;
}
