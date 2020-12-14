#pragma once

#include "ofMain.h"


class Bullet {

private:
	
	static ofSpherePrimitive sphere;
	static ofPoint GRAVITY;
	
	ofPoint position;
	ofPoint velocity;

	void setup(ofPoint position, ofPoint velocity);

public:
	
	Bullet(ofPoint position, ofPoint velocity);
	Bullet(ofPoint position);
	Bullet();
	
	ofPoint getPosition();
	void setPosition(ofPoint position);

	ofPoint getVelocity();
	void setVelocity(ofPoint velocity);
	
	void update();
	void draw();
	
};







