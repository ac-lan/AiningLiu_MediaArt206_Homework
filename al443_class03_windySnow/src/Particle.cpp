#include "Particle.h"

Particle::Particle() {
	val = ofRandom(-10000, 10000);

	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();

	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);

	frc = ofVec2f(0, 0);

	scale = ofRandom(0.5, 1.0);

	drag = ofRandom(0.97, 0.99);
	vel.y = fabs(vel.y) * 3.0;
}


void Particle::reset() {
	//the unique val allows us to set properties slightly differently for each particle
	val = ofRandom(-10000, 10000);

	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();

	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);

	frc = ofVec2f( 0, 0);

	scale = ofRandom(0.5, 1.0);

	drag = ofRandom(0.97, 0.99);
	vel.y = fabs(vel.y) * 3.0; 
}

void Particle::update(double num) {
	float WindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);

	frc.x = WindX * 0.25 + ofSignedNoise(val, pos.y * 0.04) * 0.6;
	frc.y = ofSignedNoise(val, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
	frc.x += num;
	vel *= drag;
	vel += frc * 0.4;

	if (pos.y + vel.y > ofGetHeight()) {
		pos.y -= ofGetHeight();
	}

	pos += vel;

	if (pos.x > ofGetWidth()) {
		pos.x = 0;
		
	}
	else if (pos.x < 0) {
		pos.x = ofGetWidth();

	}
	if (pos.y > ofGetHeight()) {
		pos.y =0;

	}
	else if (pos.y < 0) {
		pos.y = ofGetHeight();
		//vel.y *= -1.0;
	}

}

//------------------------------------------------------------------
void Particle::draw() {

	ofSetColor(224, 224, 224);

	ofDrawCircle(pos.x, pos.y, scale * 4.0);
}

