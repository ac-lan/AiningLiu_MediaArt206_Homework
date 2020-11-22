#include "CustomParticle.h"
CustomParticle::CustomParticle(b2World * world, float x, float y,int radius, int color,int sb) {
	static string abc[10] = {"N2","NH3","H2","O2","NO3-","H+","NH4+","e-","micro","a"};

	setPhysics(1.0, 0.5, 0.3);
	setup(world, x, y, radius);
	setVelocity(ofRandom(-80, 80), ofRandom(-80, 80));

	setData(new Data());
	auto * theData = (Data*)getData();

	theData->id = ofRandom(0, 100);
	theData->name += abc[sb];
	theData->color.setHex(color);

	theData->soundID = ofRandom(0, N_SOUNDS);
	theData->bHit = false;
}

void CustomParticle::draw() {
	auto * theData = (Data*)getData();

	if (theData) {

		float radius = getRadius();
		ofPushMatrix();
		ofTranslate(getPosition());
		ofRotateDeg(getRotation());
		ofSetColor(theData->color);
		ofFill();
		ofDrawCircle(0, 0, radius);

		float textSize = radius / 15;
		ofPushMatrix();
		ofScale(textSize, textSize);
		ofSetColor(255);
		ofDrawBitmapString(theData->name, -5*textSize, textSize);
		ofPopMatrix();

		ofPopMatrix();
	}
}

void CustomParticle::update() {
	float xpos = getPosition().x;
	float ypos = getPosition().y;
	if (ypos <= 10 || ypos >= ofGetHeight()-10) {
		float vely = getVelocity().y;
		setVelocity(getVelocity().x, -vely);
	}
}