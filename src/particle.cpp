#include "particle.hpp"

Particle::Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, double setFriction)
	: x(startX), y(startY), xVelocity(startXVelocity), yVelocity(startYVelocity), gravity(setGravity), friction(setFriction)
{
}

void Particle::update(double deltaTime)
{
	yVelocity += gravity * deltaTime;

	x += xVelocity * deltaTime;
	y += yVelocity * deltaTime;

	xVelocity *= friction * deltaTime;
	yVelocity *= friction * deltaTime;
}
