#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle
{
public:
	Particle(double startX, double startY, double startXVelocity, double startYVelocity, double setGravity, double setFriction);
	void update(double deltaTime);

private:
	double x;
	double y;
	double xVelocity;
	double yVelocity;
	double gravity;
	double friction;
};

#endif
