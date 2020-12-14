#include "bullet.h"


ofSpherePrimitive Bullet::sphere;
ofPoint Bullet::GRAVITY = ofPoint(0, -9.8 * 4, 0);


void Bullet::setup(ofPoint p, ofPoint v) {
	position = p;
	velocity = v;
}


Bullet::Bullet(ofPoint position, ofPoint velocity) {
	setup(position, velocity);
}

Bullet::Bullet(ofPoint position) {
	ofPoint velocity = ofPoint(0, 0, 0);
	setup(position, velocity);
}

Bullet::Bullet() {
	ofPoint position = ofPoint(0, 0, 0);
	ofPoint velocity = ofPoint(0, 0, 0);
	setup(position, velocity);
}


void Bullet::setPosition(ofPoint p) {
	position = p;
};
ofPoint Bullet::getPosition() {
	return position;
};

void Bullet::setVelocity(ofPoint v) {
	velocity = v;
};
ofPoint Bullet::getVelocity() {
	return velocity;
};


void Bullet::update() {

	float dt = ofGetLastFrameTime();
	
	velocity += Bullet::GRAVITY * dt;

	position += velocity * dt;
	
};


void Bullet::draw() {

	ofSetColor(ofColor::black);

	ofPushMatrix();

	ofTranslate(position);
	
	Bullet::sphere.setRadius(2);
	Bullet::sphere.draw();
	
	ofPopMatrix();

};








