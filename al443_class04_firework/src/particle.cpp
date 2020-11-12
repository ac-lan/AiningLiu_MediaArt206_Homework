#include "particle.h"
#include "ofMain.h"

particle::particle() {
	setInitialCondition(0, 0, 0, 0);
	damping = 0.01f;
}


void particle::resetForce() {
	frc.set(0, 0);
}


void particle::addForce(float x, float y) {
	frc.x = frc.x + x;
	frc.y = frc.y + y;
}


void particle::addDampingForce() {

	frc.x = frc.x - vel.x * damping;
	frc.y = frc.y - vel.y * damping;
}


void particle::setInitialCondition(float px, float py, float vx, float vy) {
	pos.set(px, py);
	vel.set(vx, vy);
}


void particle::update() {
	vel += frc;
	pos +=  vel;
}


void particle::draw() {
	ofCircle(pos.x, pos.y, 2.0);
}
